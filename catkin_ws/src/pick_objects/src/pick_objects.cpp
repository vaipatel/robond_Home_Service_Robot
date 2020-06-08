#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickupGoal;
  move_base_msgs::MoveBaseGoal dropoffGoal;

  // set up the frame parameters
  pickupGoal.target_pose.header.frame_id = "map"; // our fixed frame is the map and not the base_link
  pickupGoal.target_pose.header.stamp = ros::Time::now();
  dropoffGoal.target_pose.header.frame_id = "map"; // our fixed frame is the map and not the base_link
  dropoffGoal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach pickup
  pickupGoal.target_pose.pose.position.x = -8.0;
  pickupGoal.target_pose.pose.position.y = -2.0;
  pickupGoal.target_pose.pose.orientation.w = 1.0;
  
  // Define a position and orientation for the robot to reach dropoff
  dropoffGoal.target_pose.pose.position.x = 0;
  dropoffGoal.target_pose.pose.position.y = 0;
  dropoffGoal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach pickup
  ROS_INFO("The robot will start moving to the pickup goal..");
  ac.sendGoal(pickupGoal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its pickup goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO(".. Hooray, the robot moved to the pickup goal. It will pickup the virtual object.");
  else
    ROS_INFO(".. The robot failed to move to the pickup goal for some reason.");

  // Wait for 5 seconds
  ros::Duration(5.0).sleep();
  
  // Send the goal position and orientation for the robot to reach dropoff
  ROS_INFO(".. The robot picked up the virtual object. It will start moving to the dropoff goal..");
  ac.sendGoal(dropoffGoal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its dropoff goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO(".. Hooray, the base moved to the dropoff goal with the virtual object.");
  else
    ROS_INFO(".. The base failed to move to the dropoff goal for some reason.");
  
  // Handle ROS comm events
  ros::spin();

  return 0;
}

