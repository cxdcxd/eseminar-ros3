#ifndef _CONTROLLER_ROS_HH_
#define _CONTROLLER_ROS_HH_

#include <ros/ros.h>
#include <ros/subscriber.h>

#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <sstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/JointState.h>

#include <geometry_msgs/Twist.h>
#include <std_srvs/Empty.h>

#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>

#include <ros/package.h>
#include <mutex>        // std::mutex

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

using namespace std;

namespace eseminar 
{

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class ControllerRos 
{

public:
  ControllerRos(ros::NodeHandle &nh,ros::NodeHandle &pnh, int argc, char *argv[]);
  ~ControllerRos();

  boost::thread thread_main;

  void thrMain();

  bool app_exit = false;

  ros::Subscriber sub_laser;
  ros::Publisher pub_cmd;
  std::mutex mtx_laser;
  sensor_msgs::LaserScan current_laser;

  void callbackLaser(const sensor_msgs::LaserScan::ConstPtr &msg);
  void sendVel(double x ,double w);
  void sendGoal(float x,float y,float w);

};

} 

#endif 
