#include "rviz_camera_trajectory/camera.h"

Camera::Camera(){

    node.param("angle", angle, (double)270);
    node.param("height", height, (double)5);
    node.param("distance", distance, (double)3);
    node.param("radius", radius, (double)2);
    node.param("pitch", pitch, (double)0); 

    cp.focus.header.frame_id  = "base_link";
    cp.focus.point.y = - distance;
    cp.focus.point.z =  height;
    cp.eye.point.y = cp.focus.point.y - radius;
    cp.eye.point.z = height + (distance * tan(pitch*(PI/180)));
    cp.eye.header.frame_id  = "base_link";
    cp.up.vector.z = 1;
    cp.up.header.frame_id  = "base_link";
}

Camera::~Camera(){}

void Camera::lookRight(const ros::TimerEvent& event){
    angle -= 0.25;
    float x = cp.focus.point.x + radius * cos(angle*(PI/180));
    float y = cp.focus.point.y + radius * sin(angle*(PI/180));
    cp.eye.point.x =  x;
    cp.eye.point.y = y;
    ROS_INFO("Angle: %f, x: %f, y: %f, Height: %f", angle,x,y, height);
}

void Camera::lookLeft(const ros::TimerEvent& event){
    angle += 0.25;
    float x = cp.focus.point.x + radius * cos(angle*(PI/180));
    float y = cp.focus.point.y + radius * sin(angle*(PI/180));
    cp.eye.point.x  =  x;
    cp.eye.point.y = y;
    ROS_INFO("Angle: %f, x: %f, y: %f, Height: %f", angle,x,y, height);
}

void Camera::setMessageHeight(double h){
    cp.focus.point.z =  h;
    cp.eye.point.z = h + (distance * tan(pitch*(PI/180)));
}