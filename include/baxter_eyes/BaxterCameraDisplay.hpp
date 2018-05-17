#pragma once
#include <string>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "baxter_eyes/Point.hpp"

class BaxterCameraDisplay {
public:
/*!
* Constructor
*/
    BaxterCameraDisplay(ros::NodeHandle& nodeHandle, std::string cameraTopicLow, std::string cameraTopicUp);
    virtual ~BaxterCameraDisplay();

private:
    int nb_camera;
    static const int UP_CAMERA = 0; //camera displayed on the upper part of the screen
    static const int LOW_CAMERA = 1; //camera displayed on the lower part of the screen

    void displayImage(cv::Mat& imageToDisplay, int position);
    void lowCallback(const sensor_msgs::ImageConstPtr& msg);
    void upCallback(const sensor_msgs::ImageConstPtr& msg);
    void getMatFromMsgs(cv::Mat& matDest, const sensor_msgs::ImageConstPtr& msg);
    cv::Mat currentImageDisplayed;
    ros::NodeHandle nodeHandler;
    image_transport::ImageTransport imgTransport;
    image_transport::Publisher pub;
    image_transport::Subscriber sub[2];
};