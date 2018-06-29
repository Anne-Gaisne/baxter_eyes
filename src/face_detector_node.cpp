#include <ros/ros.h>
#include "baxter_eyes/FaceDetector.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "face_detector_node");
    ros::NodeHandle nodeHandle("~");

    if(argc < 2){
        std::cout << std::endl;
        std::cout << "Not enough arguments provided." << std::endl;
        std::cout << "Usage: <eye sample file>" << std::endl;
        return 0;
    }
    FaceDetector FaceDetector(nodeHandle, std::string(argv[1]));    

    ros::spin();
    
    return 0;
};