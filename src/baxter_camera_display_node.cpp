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
    } 
    BaxterCameraDisplay BaxterCameraDisplay(nodeHandle, std::string(argv[1]), std::string(argv[2]));    
    
    ros::spin();
    
    return 0;
};