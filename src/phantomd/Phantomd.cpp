#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include "indexing/Index.h"

using namespace std;

int main(){
    Index index("/home/_c3rberus/Documents/Github/PhantomDisk/index/.index.toml");
    
    index.remove_index(0);
    toml::table newIndex;
    newIndex.insert_or_assign("device", "new_device");
    newIndex.insert_or_assign("logical_mount", "/mnt/new_device");
    newIndex.insert_or_assign("physical_mount", "/dev/sdb");
    index.add_index(newIndex);

    cout << "Device name: " << index.name() << endl;
    cout << "generation: " << index.get_generation() << endl;
    const auto last_updated = index.get_last_updated();
    const auto last_updated_time = chrono::system_clock::to_time_t(last_updated);
    cout << "last updated: " << put_time(localtime(&last_updated_time), "%Y-%m-%d %H:%M:%S") << endl;

    return 0;

}