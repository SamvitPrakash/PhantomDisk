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
    return false;
}

bool Indexing::reconcile() {
    return false;
}