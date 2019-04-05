#ifndef __BULKRENAME_FILE_GUARD__
#define __BULKRENAME_FILE_GUARD__

#include "node.hh"

#include <fstream>
#include <string.h>
#include <iostream>
#include <string>
#include <cstdio>


class filehandler_t
{
public:
    filehandler_t()
    {
        char* tmpname = strdup("/tmp/tmpfileXXXXXXXXXX");
        mkstemp(tmpname);
        tmpfile = tmpname;
        free(tmpname);
        out = ::std::ofstream(tmpfile);
    }

    ~filehandler_t()
    {
        out.close();
        in.close();
    }

    void write_out(const nodetree_t&);
    void read_in(const nodetree_t&);

    void edit() const;
    void rename(const nodetree_t&) const;

private:
    ::std::string tmpfile;
    ::std::ifstream in;
    ::std::ofstream out;

};

#endif//__BULKRENAME_FILE_GUARD__
