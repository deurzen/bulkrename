#ifndef __BULKRENAME_FILEHANDLER_GUARD__
#define __BULKRENAME_FILEHANDLER_GUARD__

#include "node.hh"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

class FileHandler {
public:
    FileHandler() {
        char *tmpname = strdup("/tmp/tmpfileXXXXXXXXXX");
        mkstemp(tmpname);
        out = ::std::ofstream(tmpname);
        tmpfile = tmpname;
    }

    ~FileHandler() { remove(tmpfile.c_str()); };

    void write_out(const ::std::vector<Node*>& nodes);
    void edit() const { system((::std::string("vim ")+tmpfile).c_str()); }
    void read_in(const ::std::vector<Node*>& nodes);
    void rename(const ::std::vector<Node*>& nodes) const;

private:
    ::std::string tmpfile;
    ::std::ifstream  in;
    ::std::ofstream out;
};

#endif//__BULKRENAME_FILEHANDLER_GUARD__
