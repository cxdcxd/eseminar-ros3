#include "controller/controller_ros.hh"

namespace eseminar
{

ControllerRos::ControllerRos(ros::NodeHandle &nh,
                                   ros::NodeHandle &pnh,
                                   int argc,
                                   char *argv[]) :
    thread_main(&ControllerRos::thrMain,this)
{
    app_exit = false;
  
    pub_cmd = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    sub_laser = nh.subscribe("/scan", 1, &ControllerRos::callbackLaser,this);
}


void ControllerRos::thrMain()
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

    while(ros::ok() && app_exit == false)
    {

        // boost::this_thread::sleep(boost::posix_time::milliseconds(3000));
        // sendVel(0,1);
        // boost::this_thread::sleep(boost::posix_time::milliseconds(3000));
        // sendVel(0,-1);
        // boost::this_thread::sleep(boost::posix_time::milliseconds(3000));
        // sendVel(0,0);

        boost::this_thread::sleep(boost::posix_time::milliseconds(4000));
        ROS_INFO("Sending navigation goal");
        sendGoal(2,2,0)
        break;

    }
}

void ControllerRos::sendGoal(float x,float y,float w)
{
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  ROS_INFO("Action done");

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved");
  else
    ROS_INFO("The base failed to move");
}

void ControllerRos::sendVel(double x ,double w)
{
    geometry_msgs::Twist msg;
    
    msg.linear.x = x;
    msg.angular.z = w;

    pub_cmd.publish(msg);
}

void ControllerRos::callbackLaser(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    mtx_laser.lock();
    current_laser = *msg; 
    ROS_INFO_STREAM("Laser ranges" << msg->ranges.size());
    mtx_laser.unlock();
}

ControllerRos::~ControllerRos()
{
    app_exit = true;
    thread_main.interrupt();
    thread_main.join();
}

}
