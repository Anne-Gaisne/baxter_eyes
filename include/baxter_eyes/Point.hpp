#include <ros/ros.h>
#include <tf/transform_listener.h>
class Point {
    public:
        Point(float px = 0.0, float py = 0.0, float pz = 0.0, float precision = 1000.0);
        Point(tf::Vector3& , float precision = 1000.0);
        bool operator==(Point const& p2);
        bool operator!=(Point const& p2);
        float getX() const;
        float getY() const;
        float getZ() const;
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        geometry_msgs::Point toGeometryMessage();
        
    private:
        float x;
        float y;
        float z;
};