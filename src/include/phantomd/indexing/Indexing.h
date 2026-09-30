#pragma once
#include "types/StorageConfig.h"
#include <list>
#include "indexing/Index.h"

class Indexing {
    private:
        StorageConfig CONFIG;
        int GENERATION = -1;
        std::list<Index*> INDICES;
    
        bool validate();
        bool reconcile();
        void replicate();

    public:
        Indexing(StorageConfig config);
        ~Indexing();

        bool addDevice(std::string name, StorageConfig config);

        toml::array* index();

};