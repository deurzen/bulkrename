#ifndef BULKRENAME_STATEHANDLER_H
#define BULKRENAME_STATEHANDLER_H

#include <vector>
#include <string>
#include <boost/filesystem/operations.hpp>
#include "../datastructures/Node.h"

class StateHandler {
public:
    StateHandler()  = default;
    ~StateHandler() = default;

    void populate(boost::filesystem::recursive_directory_iterator dir);
    Node* convert(boost::filesystem::path path);

    void print();
    const std::vector<Node*> getnodes() const { return nodes; }

private:
    std::vector<Node*> nodes;
};

#endif //BULKRENAME_STATEHANDLER_H
