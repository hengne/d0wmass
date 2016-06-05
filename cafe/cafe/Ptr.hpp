#ifndef CAFE_PTR_HPP
#define CAFE_PTR_HPP

namespace cafe {

    //
    // template smart pointer for intrusive reference counted objects
    // using TRefCount.
    //
    template<class T>
    class Ptr {
    public:
	Ptr(T *p)
	    : fRef(p)
	{
	    if(fRef) fRef->AddReference();
	}

	template<class Y>
	Ptr(Y *p)
	    : fRef(p)
	{
	    if(fRef) fRef->AddReference();
	}

	~Ptr()
	{
	    decrement();
	}

	Ptr(const Ptr<T>& other)
	{
	    if(fRef = other.fRef) {
		fRef->AddReference();
	    }
	}

	template<class Y>
	Ptr(const Ptr<Y>& other)
	{
	    if(fRef = other.fRef) {
		fRef->AddReference();
	    }
	}

	Ptr<T>& operator=(const Ptr<T>& other)
	{
	    if(this != &other) {
		decrement();
		if((fRef = other.fRef) != 0) {
		    fRef->AddReference();
		}
	    }
	    return *this;
	}

	template<class Y>
	Ptr<T>& operator=(const Ptr<Y>& other)
	{
	    if(this != &other) {
		decrement();
		if(fRef = other.fRef) {
		    fRef->AddReference();
		}
	    }
	    return *this;
	}

	template<class Y>
	void reset(Y *p)
	{
	    decrement();
	    if(fRef = p)
		fRef->AddReference();
	}

	T *operator->()            { return fRef;  }
	T& operator*()             { return *fRef; }
	const T& operator*() const { return *fRef; }
	T *get() { return fRef; }
    private:
	void decrement()
	{
	    if(fRef && fRef->RemoveReference() == 0) {
		delete fRef;
	    }
	}
	T *fRef;
    };

}

#endif // CAFE_PTR_HPP
