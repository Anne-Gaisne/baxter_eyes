#include <ros/ros.h>
#include "baxter_eyes/BaxterArmMvmtDetector.hpp"

    BaxterArmMvmtDetector::BaxterArmMvmtDetector(ros::NodeHandle& nodeHandle):
        nodeHandler(nodeHandle) {
            pub = nodeHandler.advertise<geometry_msgs::Point>("/pointToLookAt", 100);            
            ros::Rate loop_rate(5);
            lookupTransform("/head_camera", "/left_hand", ros::Time(0), tfLeftArmPast);
            lookupTransform("/head_camera", "/right_hand", ros::Time(0), tfRightArmPast);
            geometry_msgs::Point msg;
            while (nodeHandler.ok()) {
                lookupTransform("/head_camera", "/left_hand", ros::Time(0), tfLeftArmNow);
                lookupTransform("/head_camera", "/right_hand", ros::Time(0), tfRightArmNow);
                Point originLeftNow = Point(tfLeftArmNow.getOrigin(), 100.0);
                Point originLeftPast = Point(tfLeftArmPast.getOrigin(), 100.0);
                Point originRightNow = Point(tfRightArmNow.getOrigin(), 100.0);
                Point originRightPast = Point(tfRightArmPast.getOrigin(), 100.0);
                msg = Point().toGeometryMessage();
                if (originLeftNow != originLeftPast && originRightNow != originRightPast) {
                } else if (originLeftNow != originLeftPast) {
                    msg = originLeftNow.toGeometryMessage();
                } else if (originRightNow != originRightPast) {
                    msg = originRightNow.toGeometryMessage();
                }
                tfLeftArmPast = tfLeftArmNow;
                tfRightArmPast = tfRightArmNow;
                pub.publish(msg);
                ros::spinOnce();
                loop_rate.sleep();
            }
        }

    BaxterArmMvmtDetector::~BaxterArmMvmtDetector() {}

    void BaxterArmMvmtDetector::lookupTransform(const std::string &target_frame, const std::string &source_frame, const ros::Time &time, tf::StampedTransform &transform) const {
        try{
            listener.lookupTransform(target_frame, source_frame, ros::Time(0), transform);
        } catch (tf::TransformException ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
    }
