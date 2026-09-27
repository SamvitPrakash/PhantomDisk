#include <iostream>
#include "rclone_adapter/RcloneAdapter.h"

using namespace std;

int main(){
    RcloneAdapter adapter = RcloneAdapter();

    if(adapter.probe("OneDrive:")){
        cout << "Remote is accessible." << endl;

        if(adapter.mount("OneDrive:", "/home/_c3rberus/Documents/Github/PhantomDisk/mounting_area/staging_area")){
            cout << "Mounted successfully." << endl;
        } else {
            cout << "Failed to mount." << endl;
        }
    } else {
        cout << "Remote is not accessible." << endl;
    }

    return 0;
}