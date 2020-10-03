This Project Home service robot includes the functionality of an autonomous robot performing a basic task which include picking up an object from a location and dropping t off at another location.
In order to make this robot perform these tasks, ROS packages were used. Namely;

gmapping: with the gmapping_ demo which was used to perform SLAM(simultaneous localization and Mapping), I was able to get a 2D map of my world(ChiaWorld.world). To perform this the robot was equipped with RGB-D cameras.

telebot_teleop: This was used to move the robot around the environment. with the keyboard_teleop.launch file I was able to control the movemtn of the robot as well as the speed.

turtle_rviz_launchers: This package was used to launch the 2D map in a preconfigured workspace. with the home_service.launch file I used, I was bale to launch both the robot model, trajectories and also the map in a single rviz workspace.

turtlebot_gazebo: This package was used to deploy the robot model in my ChiaWorld.world environment. This was done by linking my world file to it when executing the comman in the homeservice.sh script file.

pgm_map_creator: Because I had to change to change a wall in my environment I used the pgm_map_creator to create a 2D representation of my world. This 2D representation was used in the rviz package to simulate the robot.

pickup_objects: This folder contains a C++ code which tells the robot to go to a certain location assuming it is piccking up an object and then go to another location assuming it is dropping the object. this code was setup in such a way that each time the robot completes either the picking up or the dropping off a message is sent back. 

add_marker: This folder containes another C++ code which creates a virtual object (using markers in rviz). This object represents the supposed object that is being picked up and dropped off at a certain location by the robot. I was able to achieve this by subscribing to my robot's odometry in order to keep track of my robot's position

5 scripts were used to test the  functionality of each package but I was able to simultaneously achieve the Home service robot by using the homeservice.sh to launch all necessary files needed. These inluded launching the turtlebot in my environment, launch a 2D map of my environment as well as the turtlebot in rviz workspace, launching the amcl.launch file to localize the robot, and also the pickup_objects and add_makers files.
