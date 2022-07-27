#include "rviz_camera_trajectory/camera.h"

int main(int argc, char *argv[])
{   
    ros::init(argc, argv, "camera_placement_node");
    Camera c;
    ros::NodeHandle nh = c.getNodeHandle();
    c.publisher = nh.advertise<view_controller_msgs::CameraPlacement>("/rviz/camera_placement",10);
    c.setRtimer(nh.createTimer(ros::Duration(0.01), &Camera::lookRight , &c));
    c.setLtimer(nh.createTimer(ros::Duration(0.01), &Camera::lookLeft , &c));
    c.getLtimer().stop();
    ros:: Rate rate(100);

    while (ros::ok())
    {   
        nh.param("height", c.getHeight(), (double)1);
        c.setMessageHeight(c.getHeight());
        
        c.publisher.publish(c.getMsg());
        if (c.getAngle() == 180)
        {
            c.getRtimer().stop();
            c.getLtimer().start();
        }

        else if (c.getAngle() == 360)
        {   
            c.getLtimer().stop();
            c.getRtimer().start();
        }

        ros::spinOnce();
        rate.sleep();
    }
    
    return 0;
}