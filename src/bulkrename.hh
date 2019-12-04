#ifndef __BULKRENAME_BULKRENAME_GUARD__
#define __BULKRENAME_BULKRENAME_GUARD__

#include "parse.hh"
#include "node.hh"
#include "file.hh"

#include <filesystem>
#include <filesystem>
#include <memory>


class bulkrename_t
{
public:
    explicit bulkrename_t(int argc, char** argv)
        : m_parser(argc, argv),
          m_dir(m_parser.getargs().first ? m_parser.getargs().second[0] : "."),
          dir_it(m_dir),
          tree(!(m_parser.isset("n") || m_parser.isset("no-recurse")), m_dir)
    {}

    void setup();
    void run();

    static ::std::unique_ptr<bulkrename_t> init(int argc, char** argv);

private:
    parser_t m_parser;
    ::std::string m_dir;
    ::std::filesystem::directory_iterator dir_it;
    nodetree_t tree;
    filehandler_t filehandler;

};

#endif//__BULKRENAME_BULKRENAME_GUARD__
