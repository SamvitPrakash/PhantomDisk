#pragma once
#include "types/StorageConfig.h"
#include <list>
#include "indexing/Index.h"

class Indexing {
    private:
        StorageConfig CONFIG;
        int GENERATION = -1;
        std::list<Index*> INDICES;
    
    public:
        Indexing(StorageConfig config);
        ~Indexing();

        bool validate();
        bool reconcile();

        bool replicate();
        bool addDevice(std::filesystem::path devicePath);

};