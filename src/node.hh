#ifndef __BULKRENAME_NODE_GUARD__
#define __BULKRENAME_NODE_GUARD__

#include <string>
#include <utility>
#include <boost/filesystem/operations.hpp>
#include <iostream>

enum class nodetype_t
{
    file,
    dir
};

class File;
class Directory;

class Node {
public:
    nodetype_t type() const { return t; }
    ::std::string name() const { return n; }

    virtual const Node* fwd() const = 0;
    virtual File* getfile() = 0;
    virtual void setnewname(const ::std::string& s) = 0;

protected:
    explicit Node(nodetype_t type, ::std::string s): t(type), n(::std::move(s)) {}

    nodetype_t t{};
    ::std::string n{};

};

class File: public Node {
public:
    explicit File(const ::std::string& s): Node(nodetype_t::file, s), nn(Node::name()) {}

    const Node* fwd() const override { return nullptr; };
    File* getfile() override { return this; }

    void setnewname(const ::std::string& s) override { nn = s; }
    ::std::string getnewname() { return nn; }
    bool valid() { return nn != name(); }

    void move(const ::std::string& prefix) const {
        ::boost::filesystem::rename(prefix + name(), prefix + nn);
    }

private:
    ::std::string nn{};

};

class Directory: public Node {
public:
    explicit Directory(const ::std::string& s, Node& n): Node(nodetype_t::dir, s), next(&n) {}

    const Node*     fwd() const override { return next; }
    File* getfile() override { return next->getfile(); }

    void setnewname(const ::std::string& s) override { }

private:
    Node* next;

};

#endif//__BULKRENAME_NODE_GUARD__
