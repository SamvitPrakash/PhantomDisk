#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include "types/IndexType.h"
#include <toml++/toml.h>

struct IndexNode {
    int ID;
    IndexNode* PARENT;
    
};

struct RootNode : public IndexNode {
    const IndexType TYPE = IndexType::ROOT;
    
};

struct FileNode : public IndexNode {
    std::string NAME;
    const IndexType TYPE = IndexType::FILE;
    std::filesystem::path PHYSICAL_ADDRESS;
    
};

struct DirectoryNode : public IndexNode {
    std::string NAME;
    const IndexType TYPE = IndexType::DIRECTORY;
    std::vector<IndexNode*> CHILDREN;

};

class IndexTree {
    private:
        IndexNode* ROOT;
        int CURRENT_ID = -1;
        
    public:
        IndexTree(toml::array *index);
        ~IndexTree();
        IndexNode* root() const;
        IndexNode* operator[](int id) const;
        int get_current_id() const;

        bool new_file(int parent_id, std::filesystem::path physical_address, std::string name);
        bool new_directory(int parent_id, std::string name);

        IndexNode* operator++();
        IndexNode* operator--();

};