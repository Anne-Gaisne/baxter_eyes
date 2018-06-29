#pragma once
#include <string>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/Point.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

class FaceDetector {
    public:
    /*!
    * Constructor
    */
        FaceDetector(ros::NodeHandle& nodeHandle, std::string fileName);
        virtual ~FaceDetector();

    private:
        void detectCallback(const sensor_msgs::ImageConstPtr& msg);
        cv::CascadeClassifier facesCascade;
        ros::NodeHandle nodeHandler;
        image_transport::ImageTransport imgTransport;
        ros::Publisher publisherToPointToLookAt;
        image_transport::Publisher publisherToXDisplay;
        image_transport::Subscriber subToHeadCamera;
};
