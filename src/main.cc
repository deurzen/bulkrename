#include "bulkrename.hh"

#include <string>
#include <filesystem>


int
main(int argc, char** argv)
{
    auto brn = bulkrename_t::init(argc, argv);

    brn->setup();
    brn->run();

    return 0;
}
