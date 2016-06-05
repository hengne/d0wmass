#include <iostream>
#include <vector>

#include "cafe/Collection.hpp"
#include "cafe/Config.hpp"
#include "cafe/Event.hpp"
#include "cafe/Function.hpp"
#include "cafe/Processor.hpp"


using namespace cafe;

template<class T1, class T2> class Match {
 public:
	//Match() {};
	Match(typename  Collection<T1>::iterator obj1, std::string branch1, typename Collection<T2>::iterator obj2, std::string branch2, double dR);
	Match(const Match &src);
	virtual  ~Match() {};
	typename Collection<T1>::iterator getObj1It(); // Return the iterator of the reco object
	T1 getObj1(); // With the branch name and iterator, we can access the object
	typename Collection<T2>::iterator getObj2It(); // Return the iterator of the L3 object
	T2 getObj2(); // With the branch name and iterator, we can access the object
  double getdR();

 private:
	float _dr;
	std::string _branch1, _branch2;
	typename Collection<T1>::iterator _obj1;
	typename Collection<T2>::iterator _obj2;
	
//	ClassDef(Match, 0)
};

//
// Templated implementation must go here...
//

template <class T1, class T2> Match<T1, T2>::Match(typename Collection<T1>::iterator obj1, std::string branch1, typename Collection<T2>::iterator obj2, std::string branch2, double dR) {
	_branch1 = branch1;
	_branch2 = branch2;
	_obj1 = obj1;
	_obj2 = obj2;
	_dr = dR;
};

template <class T1, class T2> Match<T1, T2>::Match(const Match &src) {
	_branch1 = src._branch1;
	_branch2 = src._branch2;
	_obj1 = src._obj1;
	_obj2 = src._obj2;
	_dr = src._dr;
};

template <class T1, class T2> typename Collection<T1>::iterator Match<T1, T2>::getObj1It() {
	return _obj1;
};

template <class T1, class T2> T1 Match<T1, T2>::getObj1() {
	return (*_obj1);
};

template <class T1, class T2> typename Collection<T2>::iterator Match<T1, T2>::getObj2It() {
	return _obj2;
};

template <class T1, class T2> T2 Match<T1, T2>::getObj2() {
	return (*_obj2);
};

template <class T1, class T2> double Match<T1, T2>::getdR() {
	return _dr;
};
