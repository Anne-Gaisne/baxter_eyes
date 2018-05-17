#include <ros/ros.h>
#include "baxter_eyes/BaxterCameraDisplay.hpp"

BaxterCameraDisplay::BaxterCameraDisplay(ros::NodeHandle& nodeHandle, std::string cameraTopicUp, std::string cameraTopicLow):
    nodeHandler(nodeHandle),
    imgTransport(nodeHandler),
    currentImageDisplayed(600, 1024, CV_8UC4, cv::Scalar(255, 255, 255)) {
        pub = imgTransport.advertise("/robot/xdisplay", 10);
        sub[UP_CAMERA] = imgTransport.subscribe(cameraTopicUp, 100, &BaxterCameraDisplay::upCallback, this);
        if (cameraTopicLow == "none") {
            nb_camera = 1;
        } else {
            nb_camera = 2;
            sub[LOW_CAMERA] = imgTransport.subscribe(cameraTopicLow, 100, &BaxterCameraDisplay::lowCallback, this);
        }
    }

BaxterCameraDisplay::~BaxterCameraDisplay() {}

void BaxterCameraDisplay::lowCallback(const sensor_msgs::ImageConstPtr& msg) {
    cv::Mat lowImage;
    getMatFromMsgs(lowImage, msg);
    cv::putText(lowImage, "here is some text", cv::Point(5,5), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.0, cv::Scalar(255,255,255), 1, CV_AA);
    displayImage(lowImage, LOW_CAMERA);
}

void BaxterCameraDisplay::upCallback(const sensor_msgs::ImageConstPtr& msg) {
    cv::Mat upImage;
    getMatFromMsgs(upImage, msg);
    displayImage(upImage, UP_CAMERA);
}

void BaxterCameraDisplay::getMatFromMsgs(cv::Mat& matDest, const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr ptrImg;
    try {
        ptrImg = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGRA8);
        matDest = ptrImg->image;
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
}

void BaxterCameraDisplay::displayImage(cv::Mat& imageToDisplay, int position) {
    cv::resize(imageToDisplay, imageToDisplay, cv::Size(1024, 600/nb_camera), 0, 0, cv::INTER_CUBIC);
    imageToDisplay.copyTo(currentImageDisplayed(cv::Rect(0, 300*position, imageToDisplay.cols, imageToDisplay.rows)));
    sensor_msgs::ImagePtr imageMsg = cv_bridge::CvImage(std_msgs::Header(), "bgra8", currentImageDisplayed).toImageMsg();
    pub.publish(imageMsg);
}
