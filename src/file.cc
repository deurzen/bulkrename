#include "file.hh"

#include <stdio.h>
#include <sys/wait.h>
#include <set>
#include <unordered_map>


void
filehandler_t::write_out(const nodetree_t& tree)
{
    tree.print(out);
    out.close();
}

void
filehandler_t::read_in(const nodetree_t& tree)
{
    static ::std::unordered_map<::std::string, ::std::set<::std::string>> names_per_directory;

    ::std::vector<file_ptr_t> files = tree.get_files();
    ::std::vector<::std::string> filenames;

    in.open(tmpfile.c_str());

    bool conflict_found = false;

    for (auto& file : files) {
        ::std::string name;
        ::std::getline(in, name);

        if (!in)
            throw ::std::runtime_error("amount of names does not match amount of files");

        if (name.empty())
            throw ::std::runtime_error("file name must be non-empty");

        auto dirname  = file->get_path().parent_path().string();
        auto filename = file->get_path().filename().string();
        if (names_per_directory.count(dirname)) {
            if (names_per_directory[dirname].find(name) != names_per_directory[dirname].end())
                conflict_found = true;

            names_per_directory[dirname].insert(filename);
        } else {
            ::std::set<::std::string> set;
            set.insert(filename);
            names_per_directory[dirname] = set;
        }

        file->set_name(name);
    }

    in.close();

    if (conflict_found)
        throw ::std::runtime_error("multiple files within a directory are given the same name");
}

void
filehandler_t::edit() const
{
    int ret = system((::std::string("$EDITOR ") + tmpfile).c_str());
    if (WEXITSTATUS(ret) != 0)
        throw ::std::runtime_error("renaming canceled");
}

void
filehandler_t::propagate_rename(const nodetree_t& tree) const
{
    ::std::vector<file_ptr_t> files = tree.get_files();
    for (auto& file : files)
        file->rename();
}
