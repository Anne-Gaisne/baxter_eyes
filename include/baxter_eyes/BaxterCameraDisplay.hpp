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
    BaxterCameraDisplay(ros::NodeHandle& nodeHandle, std::string topicsName[]);
    virtual ~BaxterCameraDisplay();

private:
    static const int UP_LEFT_CAMERA = 0;
    static const int LOW_LEFT_CAMERA = 1;
    static const int UP_RIGHT_CAMERA = 2;
    static const int LOW_RIGHT_CAMERA = 3;

    void displayImage(cv::Mat& imageToDisplay, int positVertical, int positHorizontal, std::string frameName);
    void displayCallback(const sensor_msgs::ImageConstPtr& msg, int position);
    void getMatFromMsgs(cv::Mat& matDest, const sensor_msgs::ImageConstPtr& msg);

    int nb_camera;
    cv::Mat currentImageDisplayed;
    ros::NodeHandle nodeHandler;
    image_transport::ImageTransport imgTransport;
    image_transport::Publisher pub;
    image_transport::Subscriber subToCameraImage[4]; 
};