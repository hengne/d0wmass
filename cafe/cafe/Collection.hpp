#ifndef COLLECTION_HPP__
#define COLLECTION_HPP__

#include "TObjArray.h"
#include <iterator>
#include <cassert>

namespace cafe {

    /**
     * Wrap a TObjArray or TClonesArray in a 'STL like' container class.
     *
     * By default the Collection<T> does not own the TObjArray that
     * is passed to it and will not delete it.
     *
     * The exception is an empty collection or an assignment
     * to it. In this case it implements copy-on-write semantics.
     * 
     * The TObjArray is deleted using a "delete" statement,
     * so unless you set the kOwned bit, it shouldn't delete its contents.
     */
    
    template<class T>
    class Collection {
    public:
        typedef T      value_type;
        typedef size_t size_type;
        typedef T*     pointer_type;
        typedef T&     reference_type;
        typedef const T* const_pointer_type;
        typedef const T& const_reference_type;
    public:
	/// Pass in array. The TObjArray will not be deleted when
	/// Collection goes out of scope.
        Collection(TObjArray *data, bool owner = false )
	    : _data(0)
	{
	    if (data)
		_data = (new array_holder(data, false));
	    else {
               TObjArray *dat = new TObjArray();
               if( owner )  dat->SetOwner();
		_data = (new array_holder(dat, true));
            }
	}

	/// Copy constructor. TObjArray won't be deleted unless it is
	/// owned and the last one.
        Collection(const Collection<T>& other)
	    : _data(other._data)
	{
	    _data->inc();
	}
	/// Default constructor. New tobj array. Will be deleted when
	/// it does out of scope.
	Collection(void)
	    : _data (new array_holder(new TObjArray(), true))
	{}

	/// Delete the collection if there are no more elemements in it
        virtual ~Collection() {
	    _data->decAndDeleteIf();
	}

	/// Assign other collection to this one.
        Collection<T>& operator=(const Collection<T>& other) 
        {
            if(&other != this) {
		_data->decAndDeleteIf();
                _data = other._data;
		_data->inc();
            }
            return *this;
        }

	/// Add an item to the array. This item must be have been
	/// dynamically allocated and not on the stack. The Collection
	/// does not take ownership of the item.
	void push_back (const T& item)
	{
	    assert(item.IsOnHeap());
	    make_us_owner_of_data();
	    (*_data)->Add(const_cast<T*>(&item));
	}

	/// Add an item to the array. The collection will
	/// delete this item when it is done.
	void push_back(T *item)
	{
	    make_us_owner_of_data();
	    (*_data)->Add(item);
	}

	/// Easy [] access.
        const T& operator[](size_t index) const { return *static_cast<T*>((*_data)->At(index)); }

	/// @name Iterator access
	//@{
        class iterator;
        class const_iterator;

	/// Iterators to first element in collection.
	iterator begin() { return iterator(*_data, 0); }
        const_iterator begin() const { return const_iterator(*_data, 0); }

	/// Iterator to one past the last element in collection.
        iterator end()   { return iterator(*_data, *_data ? (*_data)->GetLast() + 1 : 0); }
        const_iterator end()   const { return const_iterator(*_data, (*_data) ? (*_data)->GetLast() + 1 : 0); }

	/// Erase entry at iterator position. Return 'next' position.
	iterator erase(iterator it) 
	{ 
	    int i = it._index;
	    make_us_owner_of_data();
	    (*_data)->RemoveAt(i);
	    (*_data)->Compress();
	    return iterator((*_data), i);
	}

	/// Erase entries between iterator positions first and last.
	iterator erase(iterator first, iterator last)
	{
	    int i = first._index;
	    make_us_owner_of_data();
	    while(i != last._index) {
		(*_data)->RemoveAt(i);
		++i;
	    }
	    (*_data)->Compress();
	    return iterator((*_data),first._index);
	}

	//@}
	
	/// Return size of collection.
        size_t size() const { return _data ? (*_data)->GetLast() + 1 : 0; }

	/// Sort a cafe::Collection<T>.
	///
	/// The predicate CompFun should be a function or a class that
	/// provides a boolean result. This predicate should be callable like
	///
	///      bool lessThan(T const& a, T const& b);
	///
	/// and should return true if a belongs before b in the sorted
	/// collection.
	///
	template <typename compare>
	void sort(iterator from, iterator to, compare CompFun)
	{
	    make_us_owner_of_data();
	    full_sort(*(*_data),from._index,to._index,CompFun);
	    return;
	} 

	/// Internal iterator class.
        class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        public:
            iterator() : _data(0), _index(0) {}
            iterator(const iterator& other) : _data(other._data), _index(other._index) {}
            iterator& operator=(const iterator& other)
            {
                if(this != &other) {
                    _data  = other._data;
                    _index = other._index;
                }
                return *this;
            }

            reference_type operator*() const { return *static_cast<T*>(_data->At(_index)); }
            pointer_type operator->() const { return static_cast<T*>(_data->At(_index)); }

            iterator& operator++()    { _index++; return *this; }
            iterator  operator++(int) { iterator  result(*this); _index++; return result; }

            iterator& operator--()    { _index--; return *this; }
            iterator  operator--(int) { iterator  result(*this); _index--; return result; }

            iterator operator+(size_t offset) const { return iterator(_data, _index + offset); }
            iterator operator-(size_t offset) const { return iterator(_data, _index - offset); }

	    // template horror ahead
	    typename std::iterator<std::random_access_iterator_tag, T>::difference_type 
	    operator-(const iterator& other) const { return _index - other._index; }

	    typename std::iterator<std::random_access_iterator_tag, T>::difference_type 
	    operator+(const iterator& other) const { return _index + other._index; }

            iterator& operator+=(size_t offset) { _index += offset; return *this; }
            iterator& operator-=(size_t offset) { _index -= offset; return *this; }

            bool operator<(const iterator& other)  const{ return _index < other._index; }
            bool operator!=(const iterator& other) const { return _index != other._index; }

        private:
            friend class Collection;
	    friend class const_iterator;
            iterator(TObjArray* data, int index = 0) : _data(data), _index(index) {}
        
            const TObjArray *_data;
            int             _index;
        };

	/// Remove ambiguity with the two iterators below. I'm not sure what the C++ standard
	/// has to say here -- need to investigate which compiler is doing the right thing. But
	/// it certianly is confusing anyway. ;-)
	typedef iterator cafe_collection_iterator;

	/// Internal const_iterator class.
        class const_iterator : public std::iterator<std::random_access_iterator_tag, T> {
        public:
            const_iterator() : _data(0), _index(0) {}
            const_iterator(const const_iterator& other) : _data(other._data), _index(other._index) {}
            const_iterator(const cafe_collection_iterator& other) : _data(other._data), _index(other._index) {}
            const_iterator& operator=(const const_iterator& other)
            {
                if(this != &other) {
                    _data  = other._data;
                    _index = other._index;
                }
                return *this;
            }

            const_reference_type operator*() const { return *static_cast<const T*>(_data->At(_index)); }
            const_pointer_type operator->() const { return static_cast<const T*>(_data->At(_index)); }

            const_iterator& operator++()    { _index++; return *this; }
            const_iterator  operator++(int) { const_iterator  result(*this); _index++; return result; }

            const_iterator& operator--()    { _index--; return *this; }
            const_iterator  operator--(int) { const_iterator  result(*this); _index--; return result; }

            const_iterator operator+(size_t offset) const { return const_iterator(_data, _index + offset); }
            const_iterator operator-(size_t offset) const { return const_iterator(_data, _index - offset); }

	    // template horror ahead
	    typename std::iterator<std::random_access_iterator_tag, T>::difference_type 
	    operator-(const const_iterator& other) const { return _index - other._index; }

	    typename std::iterator<std::random_access_iterator_tag, T>::difference_type 
	    operator+(const const_iterator& other) const { return _index + other._index; }

            const_iterator& operator+=(size_t offset) { _index += offset; return *this; }
            const_iterator& operator-=(size_t offset) { _index -= offset; return *this; }

            bool operator<(const const_iterator& other)  const{ return _index < other._index; }
            bool operator!=(const const_iterator& other) const { return _index != other._index; }

        private:
            friend class Collection;
            const_iterator(const TObjArray* data, int index = 0) : _data(data), _index(index) {}
        
            const TObjArray *_data;
            int             _index;
        };

	/// Class to help ith reference counting pointer. Public only because
	/// can't get root cint to deal with this class if private.
	class array_holder {
	public:
	    inline array_holder (TObjArray *obj, bool owned)
		: _array (obj), _count(1), _owned(owned)
	    {}
	    inline ~array_holder (void) {
		if (_owned) {
                   //_array->SetOwner();
                   delete _array;
                }
	    }

	    TObjArray * operator->() {return _array;}
	    operator TObjArray*() {return _array;}
	    operator bool () {return _array != 0;}

	    inline void inc (void) {
		_count++;
	    }
	    inline void dec (void) {
		_count--;
	    }
	    inline void decAndDeleteIf (void) {
		dec();
		if (!ownersLeft()) {
		    delete this;
		}
	    }
	    inline bool ownersLeft (void) {
		return _count != 0;
	    }
	    inline bool isOwned (void) {
		return _owned;
	    }
	private:
	    TObjArray *_array;
	    int        _count;
	    bool       _owned;
	};
    private:
	/// Holds pointer to the TObjArray and a reference count. Prevent
	/// root from trying to save it for now.
	array_holder *_data; //! 

	/// If we don't own the data array, make a copy and assume ownership. This
	/// is so we can add to a static item.
	void make_us_owner_of_data (void)
	{
	    if (_data->isOwned()) {
		return;
	    }
	    TObjArray *t = new TObjArray (*(*_data));
	    _data->decAndDeleteIf();
	    _data = new array_holder (t, true);
	}

	// Sorting routines.
	// The insert_sort routine does a simple insertion sort. This is used by the
	// full_sort method for small Collections.
	template <typename compare>
	void insert_sort(TObjArray& array, int const from, int const to, compare CompFun)
	{
	    int j = 0;
	    TObject* tmp;

	    for (int i = from; i != to; ++i) {
		j   = i;
		tmp = array.At(j);
		while ((j>from) &&
		       !CompFun(*static_cast<T const*>(array.At(j-1)),*static_cast<T const*>(tmp))) {
		    array[j] = array.At(j-1);
		    --j;
		} // while
		array[j] = tmp;
	    } // for
	    return;
	} // insert_sort

	// The partial_quicksort does quicksort for Collections larger than insertSortMax entries.
	// It is called by full_sort.
	template <typename compare>
	void partial_quicksort(TObjArray& array, int indLow, int indHigh, compare CompFun)
	{

	    const int insertSortMax = 8;
	    int i = 0;
	    int j = 0;
	    int indTurn = 0;
	    TObject const* turn = NULL;

	    if ((indHigh - indLow) > insertSortMax) {
		indTurn = (indLow+indHigh)/2;
		turn = array.At(indTurn);
		i = indLow;
		j = indHigh-1;

		swap(array,indTurn,indHigh);

		// This may not be very nice but we'll use an infinite loop
		// which we will exit via breaks.
		while (true) {
		    while (!CompFun(*static_cast<T const*>(array.At(i)),*static_cast<T const*>(turn)) &&
			   (i<=j)) {
			++i;
		    }
		    while (CompFun(*static_cast<T const*>(array.At(j)),*static_cast<T const*>(turn)) &&
			   (i<j)) {
			--j;
		    }
		    if (j<=i) {
			break;
		    }
		    swap(array,i,j);

		} // while (infinite loop)
		swap(array,indHigh,j);

		partial_quicksort(array,indLow,j-1,CompFun);
		partial_quicksort(array,j+1,indHigh,CompFun);
	    } // if (insert_sort or quicksort)

	    return;
	} 

	// This is the sorting routine for Collections. It does insertion sort for
	// small Collections and quicksort for larger ones.
	template <typename compare>
	void full_sort(TObjArray& array, int const from, int const to, compare CompFun)
	{
	    // First do a rough sort using partial_quicksort,
	    // then finish things by sorting the remaining bits
	    // using insert_sort.
	    partial_quicksort(array,from,to-1,CompFun);
	    insert_sort(array,from,to,CompFun);
	    return;
	} 

	// The swap routine is a helper for the sorting methods.
	void swap(TObjArray& array, int i, int j)
	{
	    TObject* tmp = array.At(i);
	    array[i] = array.At(j);
	    array[j] = tmp;
	    return;
	}

    public:
        ClassDef(Collection, 0);
    };

}

#endif // COLLECTION_HPP__
