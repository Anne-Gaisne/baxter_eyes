# baxter_eyes

This package allow the display of eyes that follow arm mouvement or camera's output on baxter's screen.

## Installation

Clone this repository into your catkin workspace and build it.

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
This will display the left hand camera's image on screen.
To display another camera on screen :
- make sure it is openned
- use :
```
roslaunch baxter_eyes baxter_camera_display.launch camera_up_topic:=<your camera's output topic name>
```

You can also display up to two camera on baxter screen :
```
roslaunch baxter_eyes baxter_camera_display.launch camera_up_topic:=<your first camera's output topic name> camera_low_topic:=<your second camera's output topic name>
```
