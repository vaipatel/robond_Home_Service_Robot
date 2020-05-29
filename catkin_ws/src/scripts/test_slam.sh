#!/bin/sh

# First we find our world.
export TURTLEBOT_GAZEBO_WORLD_FILE=$(rospack find my_robot)/worlds/SumWorld.world

# Now we launch various launch files.
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot_navigation gmapping_demo.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch"
