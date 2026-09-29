#pragma once
#include "types/StorageConfig.h"

class Indexing {
    private:
        StorageConfig CONFIG;
        int GENERATION;
    
    public:
        Indexing(StorageConfig config);
        ~Indexing();

        bool validate();
        bool reconcile();
        bool load();

        // Index getIndex(size_t index);

        bool replicate();

};