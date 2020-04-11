
#include <ros/ros.h>
#include <controller/controller_ros.hh>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "eseminar_controller");

  ROS_INFO("eseminar controller started");

  ros::NodeHandle nh = ros::NodeHandle();
  ros::NodeHandle pnh = ros::NodeHandle("~");

  boost::shared_ptr<eseminar::ControllerRos> en(new eseminar::ControllerRos(nh,pnh,argc,argv));

  ros::Rate loop(100);

  while(ros::ok())
  {
    ros::spinOnce();
    loop.sleep();
  }

  return 0;
}
