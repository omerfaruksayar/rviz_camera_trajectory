#include <ros/ros.h>
#include "view_controller_msgs/CameraPlacement.h"
#include <cmath>

#define PI 3.14159265359

class Camera
{
private:
    view_controller_msgs::CameraPlacement cp;
    double angle; //degree
    double height; //meter
    double distance; //meter
    double radius; //meter
    double pitch; // degree
    ros::Timer rTimer; 
    ros::Timer lTimer;
    ros::NodeHandle node;

public:
    Camera();
    ~Camera();
    double& getAngle(){return angle;}
    double& getHeight(){return height;}
    double& getDistance(){return distance;}
    double& getRadius(){return radius;}
    double& getPitch(){return pitch;}
    void setMessageHeight(double h);
    ros::NodeHandle& getNodeHandle(){return node;}
    void setRtimer(ros::Timer t){rTimer = t;}
    void setLtimer(ros::Timer t){lTimer = t;}
    ros::Timer getRtimer(){return rTimer;}
    ros::Timer getLtimer(){return lTimer;}
    void lookRight(const ros::TimerEvent& event);
    void lookLeft(const ros::TimerEvent& event);
    ros::Publisher publisher;
    view_controller_msgs::CameraPlacement getMsg(){return cp;}
};