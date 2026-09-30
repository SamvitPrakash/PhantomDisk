#include "indexing/Indexing.h"
#include "indexing/Index.h"

Indexing::Indexing(StorageConfig config) : CONFIG(config), GENERATION(0) {
    for(const auto& device : CONFIG.DEVICES) {
        INDICES.push_back(new Index(device.MOUNT_POINT));
    }
}

Indexing::~Indexing() {
    for(auto index : INDICES) {
        delete index;
    }
}

bool Indexing::validate() {
    for (const auto& index : INDICES) {
        if(!index->validate()) {
            return false;
        }
    }

    return true;
}

bool Indexing::reconcile() {
    bool equal = true;
    
    for (const auto& index : INDICES) {
        if(index->get_generation() != GENERATION) {
            equal = false;
            
            if(index->get_generation() > GENERATION) {
                GENERATION = index->get_generation();
            }
        }
    }
 
    return equal;

}

bool Indexing::replicate() {
    toml::array *replicationArray = nullptr;

    for (const auto& index : INDICES) {
        if(index->get_generation() == GENERATION) {
            replicationArray = index->index();
            break;
        }
    }

    for (const auto& index : INDICES) {
        if(index->get_generation() != GENERATION) {
            for(size_t i = 0; i < replicationArray->size(); ++i) {
                index->update_index(i, *(*replicationArray)[i].as_table());
            }

        }
    }

    return true;
}