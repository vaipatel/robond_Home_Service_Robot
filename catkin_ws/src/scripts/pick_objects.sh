#!/bin/sh

# First we find our world.
export TURTLEBOT_GAZEBO_WORLD_FILE=$(rospack find my_robot)/worlds/SumWorld.world
export TURTLEBOT_GAZEBO_MAP_FILE=$(rospack find my_robot)/maps/SumWorldMap.yaml

# Now we launch various launch files.
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch initial_pose_a:=-1.5707" &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " rosrun pick_objects pick_objects"
