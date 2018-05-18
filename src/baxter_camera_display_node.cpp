#include <iostream>
#include <ros/ros.h>
#include "baxter_eyes/BaxterCameraDisplay.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "baxter_camera_display_node");
    ros::NodeHandle nodeHandle("~");

    if(argc < 2){
        std::cout << std::endl;
        std::cout << "Not enough arguments provided." << std::endl;
        std::cout << "Usage: <camera topic name> [<camera topic name>]" << std::endl;
        return 0;
    } else if (argc > 5) {
        std::cout << std::endl;
        std::cout << "Too many arguments provided." << std::endl;
        std::cout << "Usage: only 4 camera topic name handeled" << std::endl;
        return 0;
    }
    std::string topicsName[4];
    topicsName[0] = argv[1];
    topicsName[1] = argv[2];
    topicsName[2] = argv[3];
    topicsName[3] = argv[4];
    BaxterCameraDisplay BaxterCameraDisplay(nodeHandle, topicsName);    
    
    ros::spin();
    
    return 0;
};