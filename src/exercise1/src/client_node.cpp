#include "ros/ros.h"
#include "exercise1/Reverse.h"

//#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <sstream>
#include <algorithm>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "our_client_node");
  ros::NodeHandle n;
  srand(time(nullptr));

  ros::ServiceClient client = n.serviceClient<exercise1::Reverse>("our_service_node/string");

  exercise1::Reverse srv;
  auto& input = srv.request.input;
  input.resize(10);
  std::generate(input.begin(), input.end(), [](){ return rand() % 1000; });
  // srv.request.input = {0,1,2,3,4,5,6,7,8,9};

  ros::service::waitForService("our_service_node/string", 1000);

  ROS_INFO("Sending some array...");

  if (client.call(srv))
  {
    ROS_INFO("The service returned: %d", srv.response.result);
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 1;
  }

  return 0;
}
