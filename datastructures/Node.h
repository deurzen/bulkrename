#ifndef BULKRENAME_NODE_H
#define BULKRENAME_NODE_H

#include "Datastructures.h"
#include <string>
#include <utility>
#include <boost/filesystem/operations.hpp>
#include <iostream>

class File;
class Directory;

class Node {
public:
    ds::Type    type() const { return t; }
    std::string name() const { return n; }

    virtual const Node*     fwd() const = 0;
    virtual File* getfile() = 0;
    virtual void setnewname(const std::string& s) = 0;

protected:
    explicit Node(ds::Type type, std::string s): t(type), n(std::move(s)) {}

    ds::Type t{};
    std::string n{};

};

class File: public Node {
public:
    explicit File(const std::string& s): Node(ds::Type::FILE, s), nn(Node::name()) {}

    const Node* fwd() const override { return nullptr; };
    File* getfile() override { return this; }

    void setnewname(const std::string& s) override { nn = s; }
    std::string getnewname() { return nn; }
    bool valid() { return nn != name(); }
    void move(std::string prefix) const {
        boost::filesystem::rename(prefix + name(), prefix + nn);
    }

private:
    std::string nn{};
};

class Directory: public Node {
public:
    explicit Directory(const std::string& s, Node& n): Node(ds::Type::DIR, s), next(&n) {}

    const Node*     fwd() const override { return next; }
    File* getfile() override { return next->getfile(); }

    void setnewname(const std::string& s) override { }

private:
    Node* next;
};

#endif //BULKRENAME_NODE_H
