#include <ros/ros.h>
#include "baxter_eyes/BaxterArmMvmtDetector.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "baxter_arm_mvmt_detector_node");
    ros::NodeHandle nodeHandle("~");

    BaxterArmMvmtDetector BaxterArmMvmtDetector(nodeHandle);    

    ros::spin();
    
    return 0;
};