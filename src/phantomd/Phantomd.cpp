#include <iostream>
#include <string>
#include "storage/Device.h"
#include "rclone_adapter/RcloneAdapter.h"

using namespace std;

int main(){
    RcloneAdapter adapter = RcloneAdapter();
    Device device = Device("OneDrive:", "/home/_c3rberus/Documents/Github/PhantomDisk/mounting_area/staging_area", &adapter);

    cout << "Initial Device State: " << to_string(static_cast<int>(device.state())) << endl;

    bool probe_result = device.probe();
    cout << "Probe result: " << probe_result << "\tDevice State: " << to_string(static_cast<int>(device.state())) << endl;

    if(probe_result){
        bool mount_result = device.mount();
        cout << "Mount result: " << mount_result << "\tDevice State: " << to_string(static_cast<int>(device.state())) << endl;

        if(mount_result){
            bool unmount_result = device.unmount();
            cout << "Unmount result: " << unmount_result << "\tDevice State: " << to_string(static_cast<int>(device.state())) << endl;
        }
    }

    return 0;
}