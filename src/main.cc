#include "statehandler.hh"
#include "filehandler.hh"

#include <string>
#include <boost/filesystem.hpp>


int
main(int argc, char **argv)
{
    using ::boost::filesystem::recursive_directory_iterator;

    StateHandler sh;
    recursive_directory_iterator dir( (argc > 1) ? argv[1] : "." );
    sh.populate(dir);

    FileHandler fh;
    fh.write_out(sh.getnodes());
    fh.edit();

    try {
        fh.read_in(sh.getnodes());
    } catch(const ::std::runtime_error& e) {
        ::std::cerr << "bulkrename: " << e.what() << ::std::endl;
    }

    fh.rename(sh.getnodes());

    return 0;
}
