#include "node.hh"

void
dir_t::populate(::boost::filesystem::directory_iterator dir_it)
{
    for (auto& entry : dir_it) {
        if (::boost::filesystem::is_directory(entry)) {
            dir_ptr_t dir = new dir_t(entry.path(), parent);
            children.push_back(dir);
            dir->populate(::boost::filesystem::directory_iterator(entry));
        } else if (::boost::filesystem::is_regular_file(entry)) {
            file_ptr_t file = new file_t(entry.path(), parent);
            children.push_back(file);
        }
    }
}


void
nodetree_t::populate(::boost::filesystem::directory_iterator dir_it)
{
    root->populate(dir_it);
}

void
file_t::print(::std::ostream& out) const
{
    out << path.filename().string() << ::std::endl;
}

void
dir_t::print(::std::ostream& out) const
{
    for (auto& child : children)
        child->print(out);
}

void
nodetree_t::print(::std::ostream& out) const
{
    root->print(out);
}

::std::vector<file_ptr_t>
dir_t::file_leaves() const
{
    ::std::vector<file_ptr_t> files;
    for (auto& child : children)
        if (child->get_type() == nodetype_t::dir)
            for (auto& file : dynamic_cast<dir_ptr_t>(child)->file_leaves())
                files.push_back(file);
        else
            files.push_back(dynamic_cast<file_ptr_t>(child));

    return files;
}

void
file_t::rename() const
{
    if (name != new_name)
        ::boost::filesystem::rename(path, path.parent_path().string() + "/" + new_name);
}

::std::vector<file_ptr_t>
nodetree_t::get_files() const
{
    return root->file_leaves();
}


::std::ostream&
operator<<(::std::ostream& out, node_ptr_t node)
{
    node->print(out);
    return out;
}

::std::ostream&
operator<<(::std::ostream& out, file_ptr_t file)
{

    return out;
}

::std::ostream&
operator<<(::std::ostream& out, dir_ptr_t dir)
{

    return out;
}

::std::ostream&
operator<<(::std::ostream& out, nodetree_t tree)
{
    tree.print(out);
    return out;
}
