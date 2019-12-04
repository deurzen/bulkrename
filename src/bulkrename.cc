#include "bulkrename.hh"

#include <fstream>
#include <iostream>

::std::unique_ptr<bulkrename_t>
bulkrename_t::init(int argc, char** argv)
{
    return ::std::make_unique<bulkrename_t>(argc, argv);
}

void
bulkrename_t::setup()
{
    tree.populate(dir_it);
}

void
bulkrename_t::run()
{
    filehandler.write_out(tree);

    try {
        filehandler.edit();
        filehandler.read_in(tree);
    } catch(const ::std::runtime_error& e) {
        ::std::cerr << "bulkrename: " << e.what() << ::std::endl;
        exit(1);
    }

    filehandler.propagate_rename(tree);
}
