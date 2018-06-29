#include <ros/ros.h>
#include "baxter_eyes/FaceDetector.hpp"

FaceDetector::FaceDetector(ros::NodeHandle& nodeHandle, std::string fileName):
nodeHandler(nodeHandle),
imgTransport(nodeHandler) {
    publisherToPointToLookAt = nodeHandler.advertise<geometry_msgs::Point>("/pointToLookAt", 100);
    publisherToXDisplay = imgTransport.advertise("/robot/xdisplay", 10);
    subToHeadCamera = imgTransport.subscribe("/cameras/head_camera/image", 10, &FaceDetector::detectCallback, this);
    if(!facesCascade.load(fileName)) {
        ROS_INFO_STREAM("couldn't load xml file");
    }
}

FaceDetector::~FaceDetector() {}


void FaceDetector::detectCallback(const sensor_msgs::ImageConstPtr& msg) {
    cv::Mat img;
    cv_bridge::CvImagePtr ptrImg;
    try {
        ptrImg = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGRA8);
        img = ptrImg->image;
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    std::vector<cv::Rect> faces;
    cv::Mat grayFrame;
    ROS_INFO_STREAM("test");

    cv::cvtColor( img, grayFrame, CV_BGR2GRAY );
    cv::equalizeHist( grayFrame, grayFrame );
    //facesCascade.detectMultiScale(grayFrame, faces, 1.1, 3, 0);
    facesCascade.detectMultiScale( grayFrame, faces, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
    if (faces.size() > 0 && faces[0].x/1000.0 <= 1 && faces[0].y/1000.0 <= 1) {
        geometry_msgs::Point pointMsg;
        pointMsg.x = faces[0].x/1000.0;
        pointMsg.y = faces[0].y/1000.0;
        pointMsg.z = 0;
        ROS_INFO_STREAM(pointMsg.x << " y : " << pointMsg.y);
        publisherToPointToLookAt.publish(pointMsg);
    }

    for ( size_t i = 0; i < faces.size(); i++ ) {
        cv::Rect r = faces[i];
        cv::Mat smallImgROI;
        std::vector<cv::Rect> nestedObjects;
        cv::Point center;
        cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing tool
        int radius;
 
        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5));
            center.y = cvRound((r.y + r.height*0.5));
            radius = cvRound((r.width + r.height)*0.25);
            circle( img, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( img, cvPoint(cvRound(r.x), cvRound(r.y)),
                    cvPoint(cvRound((r.x + r.width-1)), 
                    cvRound((r.y + r.height-1))), color, 3, 8, 0);
    }
    sensor_msgs::ImagePtr imageMsg = cv_bridge::CvImage(std_msgs::Header(), "bgra8", img).toImageMsg();
    publisherToXDisplay.publish(imageMsg);
    ROS_INFO_STREAM(faces.size() << "fin");

}

