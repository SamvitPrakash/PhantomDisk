#include <iostream>
#include "configurationctl/Configurationctl.h"
#include "storage/StorageManager.h"


using namespace std;

int main(){
    Configurationctl configurationctl = Configurationctl("/home/_c3rberus/Documents/Github/PhantomDisk/config/config[2].toml");
    configurationctl.load();

    StorageManager storageManager = StorageManager(configurationctl.getStorageConfig());
    cout << "PhantomDisk Daemon starting..." << endl;

    if(storageManager.mountDevice("OneDrive:")) {
        cout << "All devices mounted successfully." << endl;
    } else {
        cout << "Failed to mount one or more devices." << endl;
    }

    cout << "Performing health check..." << endl;
    int healthStatus = storageManager.healthCheck();
    cout << "Health check status: " << healthStatus <<"%" << endl;

    storageManager.unmountDevices();

    return 0;

}