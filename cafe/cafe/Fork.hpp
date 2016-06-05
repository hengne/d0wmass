#ifndef CAFE_FORK_HPP__
#define CAFE_FORK_HPP__

#include "cafe/Controller.hpp"
#include <vector>
#include <string>

namespace cafe {

    /**
     * Execute each child in parallel, ignore return codes.
     *
     * Can be used to branch into multiple parallel execution streams.
     *
     *
     * \ingroup cafe
     */

    class Fork : public Controller {
    public:
        Fork(const char *name);
    public:

        // Execute each sub Processor, always return true
        virtual bool processEvent(Event& event);

    public:
        ClassDef(Fork, 0);

    };

}

#endif // CAFE_FORK_HPP__
