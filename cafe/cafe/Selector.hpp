#ifndef CAFE_SELECTOR_HPP__
#define CAFE_SELECTOR_HPP__

#include "TSelector.h"
#include "cafe/Event.hpp"
#include "cafe/Controller.hpp"

class TTree;

namespace cafe {

#if ROOT_VERSION_CODE >= ROOT_VERSION(4,2,0)
    typedef Long64_t Entry_t;
#else
    typedef Int_t Entry_t;
#endif


    /**
     * A mixture of a Controller and a TSelector.
     * 
     * Can be passed directly to TTree::Process()
     * and will call all its children for each event.
     *
     * This allows you to call cafe Processors from the
     * root command line and with any tree.
     *
     * \ingroup cafe
     */
    class Selector : public Controller, public TSelector {
    public:
        Selector(const char *name);

	// The TSelector interface
	virtual void   Begin(TTree *tree);
	virtual void   Init(TTree *tree);
	virtual void   Terminate();
	virtual Bool_t Process(Entry_t entry);
	virtual Int_t  Version() const;

    private:
	TTree *_tree;
	Event  _event;
    public:
        ClassDef(Selector, 0);
    };
    
}

#endif // CAFE_SELECTOR_HPP__
