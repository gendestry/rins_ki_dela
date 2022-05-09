#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "exercise2/Movement.h"
#include <string>

using geometry_msgs::Twist;


int main(int argc, char** argv) {
	std::string direction = "rect";
	int duration = 10;

	switch(argc) {
		case 3: duration = atoi(argv[2]);
		case 2: direction = argv[1];
	}

	ros::init(argc, argv, "move_node_client");
	ros::NodeHandle node;

	ros::ServiceClient client = node.serviceClient<exercise2::Movement>("move_node/move");
	exercise2::Movement req;
	req.request.duration = duration;
	req.request.movement = direction;

	ros::service::waitForService("move_node/move", 1000);

	if(!client.call(req)) {
		std::cerr << "Nešto ne radi..." << std::endl;
	}
	else {
		std::cout << req.response.lastMove << std::endl; 
	}

	return 0;
}