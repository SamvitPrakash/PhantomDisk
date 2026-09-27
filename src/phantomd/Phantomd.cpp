#include <iostream>
#include <string>
#include "storage/Device.h"
#include "rclone_adapter/RcloneAdapter.h"
#include "types/DeviceState.h"

using namespace std;

int main(){
    RcloneAdapter adapter = RcloneAdapter();
    Device device = Device("OneDrive:", "/home/_c3rberus/Documents/Github/PhantomDisk/mounting_area/staging_area", &adapter);

    if(device.probe()){
        cout << "Device is ready to mount" << endl;
        cout << "Device state: " + to_string(static_cast<int>(device.state())) << endl;
        device.mount();
        cout << "Device state: " + to_string(static_cast<int>(device.state())) << endl;
        int x;
        cin >> x;
        device .unmount(); 
        cout << "Device state: " + to_string(static_cast<int>(device.state())) << endl;
    } else {
        cout << "Device is not ready to mount" << endl;
    }


    return 0;
}