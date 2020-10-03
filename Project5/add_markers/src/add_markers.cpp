#include <stdlib.h>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <complex>


 
 bool pickup_finished = false;
 bool dropoff_finished = false; 
 double pickup_xlocation = 1.5;
 double pickup_ylocation = 4.0;
 double pickup_wlocation = 1.5;
 double dropoff_xlocation = -1.5;
 double dropoff_ylocation = 2.0;
 double dropoff_wlocation = -1.5;
 double value = 0.2;
 

void object_pickup(const nav_msgs::Odometry::ConstPtr& msg)
{ 
 if (abs(msg->pose.pose.position.x-pickup_xlocation) < value && abs(msg->pose.pose.position.y-pickup_ylocation) < value && abs(msg->pose.pose.orientation.w - pickup_wlocation) )
   { 
     if (!pickup_finished)
        { pickup_finished = true;}
    } else {pickup_finished = false;}

 if (abs(msg->pose.pose.position.x-dropoff_xlocation) < value && abs(msg->pose.pose.position.y-dropoff_ylocation) < value && std::abs(msg->pose.pose.orientation.w-dropoff_wlocation))
  { 
   if (!dropoff_finished)
        { dropoff_finished = true;}
    }else {dropoff_finished = false;}
   
 
}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber marker_sub = n.subscribe("odom",1000, object_pickup);

  // Set our initial shape type to be a SPHERE
  uint32_t shape = visualization_msgs::Marker::SPHERE;
 while(ros::ok()){
     visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  
    marker.header.frame_id = "odom";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type Initially SPHERE
    marker.type = shape;

    marker.action = visualization_msgs::Marker::ADD;
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickup_xlocation;
    marker.pose.position.y = pickup_ylocation;
    marker.pose.orientation.w = pickup_wlocation;
   

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.6;
    marker.scale.y = 0.6;
    marker.scale.z = 0.6;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
   
   // Publish the marker
   while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
   
    
    marker_pub.publish(marker);
    ROS_INFO("waiting for pickup..");

    while(!pickup_finished)
    {ros::spinOnce();}

     if (pickup_finished)
  {
       // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ros::Duration(5).sleep();
      ROS_INFO("Object picked up");
      
  }
   
   while(!dropoff_finished)
    {ros::spinOnce();}

    if(dropoff_finished)
  {
    marker.pose.position.x = dropoff_xlocation;
    marker.pose.position.y = dropoff_ylocation;
    marker.pose.orientation.w = dropoff_wlocation;
    ros::Duration(5).sleep();
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Object at the Dropoff location");
    return 0;
  }
   
   }
   

}

