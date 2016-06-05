#ifndef CAFE_HISTOGETTER_HPP_
#define CAFE_HISTOGETTER_HPP_

#include <string>
#include "cafe/Variables.hpp"

class TObject;
class TTree;

namespace cafe {

    /// Utility function to speed up histogramming of method calls.
    /// Only used internally by Hist1D.
    class HistoGetter {
    public:
	HistoGetter(const cafe::Variables& vars);
	virtual ~HistoGetter();
	virtual float get(TObject *obj) = 0;

	static void parse(const std::string& expression, std::string& branch, std::string& method);
	static HistoGetter *create(TTree *tree, const std::string& branch, const std::string& method);

	const cafe::Variables& vars() const;

    private:
	const cafe::Variables _vars;
    };

}

#endif // CAFE_HISTOGETTER_HPP_
