# udacityProject Go Chase It.
In this project, I created two ROS packages in my catkin_ws/src folder which are my_robot and ball_chaser:

my_robot package contains the differential robot model with the unified robot description is created, the gazebo world or environment and the white ball which would be chased my the robot. 

ball_chaser package contains drive_bot.cpp (c++ node) which would program the robot to move using the ball_Cahser/command_robot service. This controls the linear and angular velocities of the robot. The ball_chaser pckage also containes the process_image.cpp that reads the robot’s camera image, it analyzes the image to determine the location and position of the white ball. If the white ball is found it requests a service to drive the robot to the position of the white ball.

HOW TO RUN THIS PROJECT:
In your workspace create a catkin_ws folder, In the catkin_ws folder create a src
compile catkin_ws using the command "catkin_make". 
Then clone the my_robot and ball_chaser packages into your src folder using the command "git clone  https://github.com/aligwekc/udacity-Go_chase_it.git " 
After successfully cloning the packages build using "source devel/setup.bash" and 
launch the robot in the gazebo world using "roslaunch my_robot world.launch" 
open a new terminal then "source devel/setup.bash"
run the ball_chaser package using "roslaunch ball_chaser ball_chaser.launch.
