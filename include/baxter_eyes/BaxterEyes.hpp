#pragma once
#include <string>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/Point.h>
#include "baxter_eyes/Point.hpp"

namespace baxter_eyes {
    class BaxterEyes {
        public:
        /*!
        * Constructor
        */
            BaxterEyes(ros::NodeHandle& nodeHandle, std::string pathEyeContour, std::string pathPupil);
            virtual ~BaxterEyes();

        private:
            void lookCallback(const geometry_msgs::Point::ConstPtr& msg);
            void displayEyes(const Point& pointToLookAt);
            Point getPupilPosition(const Point& pointToLookAt);
            void overlayImage(cv::Mat* src, cv::Mat* overlay, const Point& location); //used to overlay image using the alpha channel (transparency)

            ros::NodeHandle nodeHandler;
            image_transport::ImageTransport imgTransport;
            image_transport::Publisher publisherToXDisplay;
            ros::Subscriber subscriberPointToLookAt;
            cv::Mat eyeContour;
            cv::Mat pupil;
    };
}