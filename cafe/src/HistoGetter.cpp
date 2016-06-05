
#include "cafe/HistoGetter.hpp"

#include "TObject.h"
#include "TTree.h"
#include "TBranchElement.h"
#include "TObjString.h"

#include "tmb_tree/TMBLorentzVector.hpp"
#include "tmb_tree/TMBL2Base.hpp"
#include "tmb_tree/TMBL3Base.hpp"
#include <cassert>

namespace {

    template<class T, class RET = float>
    class HistoGetterImpl : public cafe::HistoGetter {
    public:
	typedef RET (T::*GETTER)() const;

	HistoGetterImpl(GETTER getter, const cafe::Variables& vars)
          : HistoGetter(vars),
            _getter(getter)
	{
	}

	virtual float get(TObject *obj) 
	{
	    if(T *ptr = dynamic_cast<T*>(obj)) {
		return (float )(ptr->*_getter)();
	    } else {
		assert(false);
		return 0.0;
	    }
	}
    private:
	GETTER _getter;
    };

    template<class BASE, class RET>
    HistoGetterImpl<BASE,RET> *make(const std::string& method, const cafe::Variables& vars)
    {
	struct Method { 
	    const char *name;
	    typename HistoGetterImpl<BASE,RET>::GETTER getter;
	};

	static Method methods[] = {
	    { "Pt", &BASE::Pt },
	    { "E", &BASE::E },
	    { "Eta", &BASE::Eta },
	    { "Phi", &BASE::Phi },
	    { "Px", &BASE::Px },
	    { "Py", &BASE::Py },
	    { "Pz", &BASE::Pz },
	    { 0, 0 }
	};

	for(Method* ptr = methods; ptr->name != 0; ptr++) {
	    if(method == ptr->name) {
		return new HistoGetterImpl<BASE,RET>(ptr->getter, vars);
	    }
	}

	return 0;
    }
}

namespace cafe {

    HistoGetter::HistoGetter(const cafe::Variables& vars)
	: _vars(vars)
    {
    }

    HistoGetter::~HistoGetter()
    {
    }

    void HistoGetter::parse(const std::string& expression,
			    std::string& branch,
			    std::string& method)
    {
	// check for a string of the form: IDENT.IDENT()
	// and nothing else in the input.
	
	// quick test for any special chars
	if(expression.find_first_of("[]->+/*&|<>!%$") != std::string::npos) {
	    return;
	}
	
	TString s(expression.c_str());
	TObjArray *a = s.Tokenize(".(");
	if(a->GetLast() == 2 &&
	   ((TObjString *)(a->At(2)))->GetString() == ")") {
	    // lets try it...
	    branch = ((TObjString *)a->At(0))->GetString().Data();
	    method = ((TObjString *)a->At(1))->GetString().Data();
	}
	delete a;
    }


    HistoGetter *HistoGetter::create(TTree *tree, const std::string& branch,
				     const std::string& method)
    {
	if(TBranchElement *br = dynamic_cast<TBranchElement*>(tree->GetBranch(branch.c_str()))) {
	    if(TClass *cl = TClass::GetClass(br->GetClonesName())) {
		if(cl->InheritsFrom("TMBLorentzVector")) {
		    return make<TMBLorentzVector,Double_t>(method, cafe::Variables("fX","fY","fZ", "fM"));
		} else if(cl->InheritsFrom("TMBL2Base")) {
		    return make<TMBL2Base,float>(method, cafe::Variables("et", "ieta", "iphi" ));
		} else if(cl->InheritsFrom("TMBL3Base")) {
		    return make<TMBL3Base,float>(method, cafe::Variables("et", "eta", "phi" ));
		}
	    }
	}
	// fall through, return 0 => no optimization
	return 0;
    }

    const cafe::Variables& HistoGetter::vars() const
    {
	return _vars;
    }

}
