/**
*   Author : bhaskar (bhaskarsuper9000@gmail.com)
*   This demo shows you how to write a simple program to 
*   generate a sine wave & view it using rqt_plot
*/
#include "ros/ros.h"
#include "std_msgs/Float32.h"

int main(int argc, char **argv)
{
    /**
    *   ros::init(): argc & argv are passed for any remappings
    *   that might be needed. Third param is node name
    */
    ros::init(argc, argv, "wave");

    ros::NodeHandle n;  //for any external communications with ROS

    /**
    *   advertise(): To inform the master that you want to publish
    *   Param1 is the name of topic. Param 2 is size of msg queue
    */
    ros::Publisher gen_pub = n.advertise<std_msgs::Float32> ("wave_gen", 100);

    ros::Rate loop_rate(10);

    //Decraled variables
    std_msgs::Float32 x,y;
    x.data = 0;
    
    while (ros::ok())
    {
        y.data =  sin(x.data);
        x.data += 0.1;      //Increment for next iteration
        x.data =  x.data>360 ? x.data-360 : x.data;

        gen_pub.publish(y);   //Actually publish
        ROS_INFO("Published y = %f", y.data);

        ros::spinOnce();    //This helps to check for pending callbacks
        loop_rate.sleep();  //sleeps for a time that maintains the rate
    }
}
