#include "ros/ros.h"
#include "exercise1/Reverse.h"

#include <string>
#include <iostream>
#include <sstream>
#include <numeric>
#include <iterator>


bool manipulate(exercise1::Reverse::Request  &req, exercise1::Reverse::Response &res) {
  auto& input = req.input;
  res.result = accumulate(input.begin(), input.end(), 0);

  std::stringstream ss;
  std::copy(input.begin(), input.end(), std::ostream_iterator<int>(ss, " "));
  std::string sth = ss.str();
  sth.erase(sth.size() - 1);

  ROS_INFO("request: (%s) response: %d", sth.c_str(), res.result);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "our_service_node");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("our_service_node/string", manipulate);
  ROS_INFO("I am ready to sum your array!");
  ros::spin();

  return 0;
}
