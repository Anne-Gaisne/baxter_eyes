#include "baxter_eyes/Point.hpp"

Point::Point(float px, float py, float pz, float precision) {
    x = std::roundf(px * (int) precision) / precision;
    y = std::roundf(py * (int) precision) / precision;
    z = std::roundf(pz * (int) precision) / precision;
}

Point::Point(tf::Vector3& origin, float precision) {
    x = std::roundf(origin.getX() * (int) precision) / precision;
    y = std::roundf(origin.getY() * (int) precision) / precision;
    z = std::roundf(origin.getZ() * (int) precision) / precision;
}

float Point::getX() const {
    return this->x;
}

float Point::getY() const {
    return this->y;
}

float Point::getZ() const {
    return this->z;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

void Point::setZ(float z) {
    this->z = z;
}

geometry_msgs::Point Point::toGeometryMessage() {
    geometry_msgs::Point msg;
    msg.x = this->getX();
    msg.y = this->getY();
    msg.z = this->getZ();
    return msg;
}

bool Point::operator==(Point const& p2) {
    return (this->getX() == p2.getX() && this->getY() == p2.getY() && this->getZ() == p2.getZ());
}

bool Point::operator!=(Point const& p2) {
    return (this->getX() != p2.getX() || this->getY() != p2.getY() || this->getZ() != p2.getZ());
}