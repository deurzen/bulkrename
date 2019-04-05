#ifndef __BULKRENAME_BULKRENAME_GUARD__
#define __BULKRENAME_BULKRENAME_GUARD__

#include "node.hh"
#include "file.hh"

#include <filesystem>
#include <filesystem>
#include <memory>


class bulkrename_t
{
public:
    explicit bulkrename_t(const ::std::string& dir)
        : dir_it(dir), tree(dir)
    {}

    void setup();
    void run();

    static ::std::unique_ptr<bulkrename_t> init(const ::std::string&);

private:
    ::std::filesystem::directory_iterator dir_it;
    nodetree_t tree;
    filehandler_t filehandler;

};

#endif//__BULKRENAME_BULKRENAME_GUARD__
