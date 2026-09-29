#include <iostream>
#include "configurationctl/Configurationctl.h"
#include "storage/StorageManager.h"


using namespace std;

int main(){
    Configurationctl configurationctl = Configurationctl("/home/_c3rberus/GitHub/PhantomDisk/config/test.toml");
    configurationctl.load();

    StorageManager storageManager = StorageManager(configurationctl.getStorageConfig());
    cout << "PhantomDisk Daemon starting..." << endl;

    if(storageManager.mountDevice("OneDrive")) {
        cout << "All devices mounted successfully." << endl;
    } else {
        cout << "Failed to mount one or more devices." << endl;
    }

    storageManager.unmountDevices();

    return 0;

}