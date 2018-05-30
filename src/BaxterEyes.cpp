#include <ros/ros.h>
#include "baxter_eyes/BaxterEyes.hpp"

namespace baxter_eyes {
    BaxterEyes::BaxterEyes(ros::NodeHandle& nodeHandle, std::string pathEyeContour, std::string pathPupil) :
        nodeHandler(nodeHandle),
        imgTransport(nodeHandler) {
            eyeContour = cv::imread(pathEyeContour, CV_LOAD_IMAGE_UNCHANGED);
            pupil = cv::imread(pathPupil, CV_LOAD_IMAGE_UNCHANGED);
            pub = imgTransport.advertise("/robot/xdisplay", 100);
            sub = nodeHandler.subscribe("/pointToLookAt", 100, &BaxterEyes::lookCallback, this);
        }

    BaxterEyes::~BaxterEyes() {}

    void BaxterEyes::lookCallback(const geometry_msgs::Point::ConstPtr& msg) {
        Point pointSended = Point(msg->x, msg->y, msg->z);
        displayEyes(pointSended);
    }

    void BaxterEyes::displayEyes(const Point& pointToLookAt) {
        cv::Mat background(600, 1024, eyeContour.type(), cv::Scalar(255, 255, 255));
        Point pupilPosition = getPupilPosition(pointToLookAt);

        //combine the contour with the pupil at the right position in a single image to create a message to publish on xDisplay topic
        overlayImage(&background, &pupil, pupilPosition);
        overlayImage(&background, &eyeContour, Point());
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgra8", background).toImageMsg();
        pub.publish(msg);
    }

    Point BaxterEyes::getPupilPosition(const Point& pointToLookAt) {
        Point pupilPosit = Point();
        if (pointToLookAt.getZ() >= 0) {
            if (pointToLookAt.getX() <= -1) {
                pupilPosit.setX(-100.0);
            } else if (pointToLookAt.getX() >= 1) {
                pupilPosit.setX(100.0);
            } else {
                pupilPosit.setX(pointToLookAt.getX()*100.0);
            }
            if (pointToLookAt.getY() <= -1) {
                pupilPosit.setX(-100.0);
            } else if (pointToLookAt.getY() >= 1) {
                pupilPosit.setX(100.0);
            } else {
                pupilPosit.setY(pointToLookAt.getY()*-100.0);
            }
        }
        return pupilPosit;
    }

    void BaxterEyes::overlayImage(cv::Mat* src, cv::Mat* overlay, const Point& location) {
        for (int y = std::max(location.getY(), 0.0f); y < src->rows; ++y) {
            int fY = y - location.getY();
            if (fY < overlay->rows) {
                for (int x = std::max(location.getX(), 0.0f); x < src->cols; ++x) {
                    int fX = x - location.getX();
                    if (fX < overlay->cols) {
                        double opacity = ((double)overlay->data[fY * overlay->step + fX * overlay->channels() + 3]) / 255;
                        for (int c = 0; opacity > 0 && c < src->channels(); ++c) {
                            unsigned char overlayPx = overlay->data[fY * overlay->step + fX * overlay->channels() + c];
                            unsigned char srcPx = src->data[y * src->step + x * src->channels() + c];
                            src->data[y * src->step + src->channels() * x + c] = srcPx * (1. - opacity) + overlayPx * opacity;
                        }
                    }
                }
            }
        }
    }

}