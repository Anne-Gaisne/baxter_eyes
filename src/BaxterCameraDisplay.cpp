#include <ros/ros.h>
#include "baxter_eyes/BaxterCameraDisplay.hpp"

BaxterCameraDisplay::BaxterCameraDisplay(ros::NodeHandle& nodeHandle, std::string topicsName[]):
    nb_camera(0),
    imgTransport(nodeHandle),
    currentImageDisplayed(600, 1024, CV_8UC4, cv::Scalar(255, 255, 255)) {
        publisherToXDisplay = imgTransport.advertise("/robot/xdisplay", 10);
        int i = 0;
        int posit = UP_LEFT_CAMERA;
        while (i < 4 && topicsName[i]!="none") {
            nb_camera++;
            subToCameraImage[i] = imgTransport.subscribe(topicsName[i], 100, boost::bind(&BaxterCameraDisplay::displayCallback, this, _1, posit));
            posit++;
            i++;
        }
    }

BaxterCameraDisplay::~BaxterCameraDisplay() {}

void BaxterCameraDisplay::displayCallback(const sensor_msgs::ImageConstPtr& msg, int position) {
    cv::Mat img;
    getMatFromMsgs(img, msg);
    //get frame id to display
    std::string frameStr = msg->header.frame_id;
    std::replace( frameStr.begin(), frameStr.end(), '/', ' ');
    std::replace( frameStr.begin(), frameStr.end(), '_', ' ');
    //get position of the image to display on screen
    int positVertical = 0;
    int positHorizontal = 0;
    if (position == LOW_LEFT_CAMERA || position == LOW_RIGHT_CAMERA) {
        positVertical = 1;
    }
    if (position == LOW_RIGHT_CAMERA || position == UP_RIGHT_CAMERA) {
        positHorizontal = 1;
    }    
    displayImage(img, positVertical, positHorizontal, frameStr);
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

void BaxterCameraDisplay::displayImage(cv::Mat& imageToDisplay, int positVertical, int positHorizontal, std::string frameName) {
    int width = 1024;
    int height = 600;
    if (nb_camera >= 3) {
        width = width/2;
    }
    if (nb_camera >= 2) {
        height = height/2;
    }
    //resize camera image to fill its given part on screen
    cv::resize(imageToDisplay, imageToDisplay, cv::Size(width, height), 0, 0, cv::INTER_CUBIC);
    //add the resized image to the currentImageDisplayed to get the correct image to display on the full screen
    imageToDisplay.copyTo(currentImageDisplayed(cv::Rect(512*positHorizontal, 300*positVertical, imageToDisplay.cols, imageToDisplay.rows)));
        
    //add frame name on the image
    int fontface = cv::FONT_HERSHEY_DUPLEX;
    double scale = 1.0;
    int thickness = 1;
    int baseline = 0;
    cv::Point pt((25 + 512*positHorizontal), (50 + 300*positVertical));
    cv::Size text = cv::getTextSize(frameName, fontface, scale, thickness, &baseline);
    cv::rectangle(currentImageDisplayed, pt + cv::Point(0, baseline+5), pt + cv::Point(text.width, -text.height-5), CV_RGB(0,0,0), CV_FILLED);
    cv::putText(currentImageDisplayed, frameName, pt, fontface, scale, CV_RGB(255,255,255), thickness, 8);
    
    sensor_msgs::ImagePtr imageMsg = cv_bridge::CvImage(std_msgs::Header(), "bgra8", currentImageDisplayed).toImageMsg();
    publisherToXDisplay.publish(imageMsg);
}
