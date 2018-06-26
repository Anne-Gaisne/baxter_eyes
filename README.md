# baxter_eyes

This package allow the display of eyes that follow arm mouvement or camera's output on baxter's screen.

## Installation

Clone this repository into your catkin workspace and build it.

If you want to use the file quaternion-transform.cpp :
```
cd ~/catkin_ws/src/baxter_eyes/util
cp quaternion-transform.cpp ~/catkin_ws
cd ~/catkin_ws
g++ -o quaternion-transform quaternion-transform.cpp -std=c++11
```

## Usage

To display the eyes :
```
roslaunch baxter_eyes baxter_eyes.launch
```
The eyes will follow the arm that moves.

To display camera's image :
```
roslaunch baxter_eyes baxter_camera_display.launch
```
This will display the left hand camera's, the right hand camera's and the kinect's image on screen.
To display another camera on screen :
- make sure it is openned
- use :
```
rosrun baxter_eyes baxter_camera_display.launch <camera topic name> <camera topic name> <camera topic name> <camera topic name>
```
If you give an unkown topic or a topic that doesn't send message with type sensor_msgs/Image, it will not be displayed thus you can only display one camera on screen just by putting your camera topic name first and "none" for other topic name.
