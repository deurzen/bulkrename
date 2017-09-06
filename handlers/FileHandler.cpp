//
// Created by deurzen on 9/1/17.
//

#include <cstdlib>
#include <cstring>
#include "FileHandler.h"

void FileHandler::write_out(const std::vector<Node*> &nodes) {
    for (Node* n : nodes) {
        out << n->getfile()->name() << std::endl;
    }
    out.close();
}

void FileHandler::read_in(const std::vector<Node*> &nodes) {
    in.open(tmpfile.c_str());
    for (Node* n : nodes) {
        std::string name;
        std::getline(in, name);
        if(!in) throw std::runtime_error("amount of new files does not match amount of old files");
        n->getfile()->setnewname(name);
    }
    in.close();
}

void FileHandler::rename(const std::vector<Node*> &nodes) const {
    for (Node* n : nodes) {
        File* file = n->getfile();
        if (file->valid()) file->move(n->name());
    }
}
