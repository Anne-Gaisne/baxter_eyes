#pragma once
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Point.h>
#include "baxter_eyes/Point.hpp"

    class BaxterArmMvmtDetector {
        public:
        /*!
        * Constructor
        */
            BaxterArmMvmtDetector(ros::NodeHandle& nodeHandle);
            virtual ~BaxterArmMvmtDetector();

        private:
            void lookupTransform(const std::string &target_frame, const std::string &source_frame, const ros::Time &time, tf::StampedTransform &transform) const;
            //used for communication with the robot
            ros::NodeHandle nodeHandler;
            ros::Publisher publishPointToLookAt;
            tf::TransformListener listenerToArmTransform;

            //used for knowing arm movement
            tf::StampedTransform tfLeftArmPast;
            tf::StampedTransform tfLeftArmNow;
            tf::StampedTransform tfRightArmPast;
            tf::StampedTransform tfRightArmNow;
    };
