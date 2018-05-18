#include <iostream>
#include <ros/ros.h>
#include "baxter_eyes/BaxterEyes.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "baxter_eyes_node");
    ros::NodeHandle nodeHandle("~");

    if(argc < 3){
        std::cout << std::endl;
        std::cout << "Not enough arguments provided." << std::endl;
        std::cout << "Usage: <eye_contour image file> <pupil image file>" << std::endl;
        return 0;
    }

    baxter_eyes::BaxterEyes BaxterEyes(nodeHandle, std::string(argv[1]), std::string(argv[2]));    

    ros::spin();
    
    return 0;
};