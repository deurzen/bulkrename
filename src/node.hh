#ifndef __BULKRENAME_NODE_GUARD__
#define __BULKRENAME_NODE_GUARD__

#include <filesystem>
#include <fstream>
#include <iostream>


enum class nodetype_t
{
    file,
    dir
};


typedef class node_t* node_ptr_t;

typedef class node_t
{
public:
    /* node_t(nodetype_t _type, node_ptr_t _parent, const ::std::string& _name) */
    node_t(nodetype_t _type, node_ptr_t _parent, const ::std::filesystem::path& _path)
        : type(_type), parent(_parent), path(_path)
    {}

    virtual bool has_next() const = 0;
    virtual void print(::std::ostream& out) const = 0;

    const nodetype_t get_type() const { return type; }
    const ::std::filesystem::path get_path() const { return path; }

protected:
    nodetype_t type;
    node_ptr_t parent;
    ::std::filesystem::path path;
    ::std::string name;

}* node_ptr_t;

::std::ostream& operator<<(::std::ostream&, node_ptr_t);


typedef class file_t : public node_t
{
public:
    explicit file_t(const ::std::filesystem::path& path, node_ptr_t parent)
        : node_t(nodetype_t::file, parent, path), new_name(path.string())
    {}

    bool has_next() const override { return false; }
    void print(::std::ostream& out) const override;

    void set_name(const ::std::string& name) { new_name = name; }

    void rename() const;

private:
    ::std::string new_name;

}* file_ptr_t;

::std::ostream& operator<<(::std::ostream&, file_ptr_t);


typedef class dir_t : public node_t
{
public:
    explicit dir_t(const ::std::filesystem::path& path, node_ptr_t parent)
        : node_t(nodetype_t::dir, parent, path)
    {}

    void populate(::std::filesystem::directory_iterator);
    bool has_next() const override { return !children.empty(); }
    void print(::std::ostream& out) const override;

    ::std::vector<file_ptr_t> file_leaves() const;

private:
    ::std::vector<node_ptr_t> children;

}* dir_ptr_t;

::std::ostream& operator<<(::std::ostream&, dir_ptr_t);


class nodetree_t
{
public:
    explicit nodetree_t(const ::std::string& _root_name)
        : root_name(_root_name), root(new dir_t(_root_name, nullptr))
    {}

    nodetree_t& operator=(const nodetree_t&) = delete;
    nodetree_t(const nodetree_t&) = delete;

    void populate(::std::filesystem::directory_iterator);
    void print(::std::ostream& out) const;

    ::std::vector<file_ptr_t> get_files() const;

private:
    ::std::string root_name;
    dir_ptr_t root;

};

::std::ostream& operator<<(::std::ostream&, nodetree_t);


#endif//__BULKRENAME_NODE_GUARD__
