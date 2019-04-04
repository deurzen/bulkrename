#ifndef __BULKRENAME_STATEHANDLER_GUARD__
#define __BULKRENAME_STATEHANDLER_GUARD__

#include <boost/filesystem/operations.hpp>
#include "node.hh"

#include <vector>
#include <string>

class StateHandler {
public:
    StateHandler()  = default;
    ~StateHandler() = default;

    void populate(::boost::filesystem::recursive_directory_iterator dir);
    Node* convert(::boost::filesystem::path path);

    void print();
    const std::vector<Node*> getnodes() const { return nodes; }

private:
    std::vector<Node*> nodes;
};

#endif//__BULKRENAME_STATEHANDLER_GUARD__
