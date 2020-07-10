#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <move_base_msgs/MoveBaseAction.h> //action interface to the navigation stack.
#include <actionlib/client/simple_action_client.h>
#include <iostream>
#include <string>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

geometry_msgs::TransformStamped tf_listener(){
	tf2_ros::Buffer tfBuffer;
	tf2_ros::TransformListener tfListener(tfBuffer);
	geometry_msgs::TransformStamped transformGoalMsgs;
	std::string select;
	while(1){
		try{
			transformGoalMsgs = tfBuffer.lookupTransform("map", "ar_marker_0", ros::Time(0),ros::Duration(1.0));
				ROS_INFO("x %f, y %f z %f",transformGoalMsgs.transform.translation.x,
																		 transformGoalMsgs.transform.translation.y,
																		 transformGoalMsgs.transform.translation.z);
		}
			catch(tf2::TransformException &ex){
			ROS_WARN("%s",ex.what());
			ros::Duration(0.5).sleep();
			continue;
		}
		ROS_INFO("Press the ENTER when you are in the desire position");
		ROS_INFO("Other key + ENTER for continue");
		std::getline(std::cin, select);
		if(select == ""){
			break;
			//return transformGoalMsgs;
		}else{
			continue;
		}
	}
	return transformGoalMsgs;
}

bool moveBase(	geometry_msgs::TransformStamped goalPose){
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true); //Constructs action client

	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "map"; //Reference frame for location. In this case relative to robot
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = goalPose.transform.translation.x * 1.5; // Se multiplica para enviar el robot más lejos debido a la reducidad vision de la camara
	goal.target_pose.pose.position.y = goalPose.transform.translation.y * 2.0; // Se multiplica para enviar el robot más lejos debido a la reducida vision de la camara
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending goal (%f,%f)",goal.target_pose.pose.position.x,
																	goal.target_pose.pose.position.y);
	ac.sendGoal(goal);

	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		ROS_INFO("Hooray, the base achived the Goal Pose (%f,%f)",
															goal.target_pose.pose.position.x,
															goal.target_pose.pose.position.y);
		return 1;
	}else{
		ROS_INFO("The base failed to move for some reason");
		return 0;
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "camera_navigation_goals");
	ros::NodeHandle n;
	geometry_msgs::TransformStamped transGoalMsgs;
	transGoalMsgs = tf_listener();
	moveBase(transGoalMsgs);
	ros::spin();   //cambiar por ros::spin_one() y finalizar el nodo
	return 0;
}
