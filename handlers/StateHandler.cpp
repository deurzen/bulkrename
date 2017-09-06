//
// Created by deurzen on 9/1/17.
//

#include <iostream>
#include "StateHandler.h"
#include "../datastructures/Node.h"

void StateHandler::populate(boost::filesystem::recursive_directory_iterator dir)
{
    boost::filesystem::recursive_directory_iterator end;
    for (; dir != end; ++dir)
        if (is_regular_file(dir->path()))
            nodes.push_back(convert(dir->path()));
}

Node* StateHandler::convert(boost::filesystem::path path)
{
    std::string dir, file;
    dir  = path.parent_path().string() + "/";
    file = path.filename().string();

    File* f = new File(file);
    return new Directory(dir, *f);
}

void StateHandler::print() {
    for (Node* f : nodes)
        std::cout << f->name() << f->fwd()->name() << std::endl;
}
