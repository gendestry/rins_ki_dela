#include <ros/ros.h>
#include "exercise2/Movement.h"
#include <geometry_msgs/Twist.h>

#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using geometry_msgs::Twist;

bool serviceHandler(exercise2::Movement::Request&, exercise2::Movement::Response&);
Twist circular(int);
Twist rectangular(int);
Twist triangular(int);
Twist random(int);

ros::Publisher pub;

int main(int argc, char** argv) {
	srand(time(nullptr));

	ros::init(argc, argv, "move_node");
	ros::NodeHandle node;
	pub = node.advertise<Twist>("turtle1/cmd_vel", 1000);

	ros::ServiceServer service = node.advertiseService("move_node/move", serviceHandler);
	ros::spin();

	return 0;
}


bool serviceHandler(exercise2::Movement::Request& req, exercise2::Movement::Response& res) {
	int duration = req.duration;
	std::string& direction = req.movement;

	ros::Rate r(1);
	Twist(*fun)(int);

	if(direction == "circ") { fun = circular; }
	else if(direction == "rect") { fun = rectangular; }
	else if(direction == "tri") { fun = triangular; }
	else if(direction == "rng") { fun = random; }
	else { std::cerr << "unknown thingy: " << direction << std::endl; fun = circular; }
	
	for(int step = 0; duration > step; step++) {
		Twist ret = fun(step);
		pub.publish(ret);
		r.sleep();
	}

	return true;
}


Twist circular(int step) {
	Twist tw;
	tw.linear.x = 0.5;
	tw.angular.z = 0.5;
	return tw;
}

Twist rectangular(int step) {
	Twist tw;
	tw.linear.x = 0.5;

	if (step % 5 == 0) {
		tw.linear.x = 0;
		tw.angular.z = (1 / 4.0) * 2 * 3.1415926535897932384626433;
	}
	return tw;
}

Twist triangular(int step) {
	Twist tw;
	tw.linear.x = 0.5;

	if (step % 5 == 0) {
		tw.linear.x = 0;
		tw.angular.z = (1 / 3.0) * 2 * 3.1415926535897932384626433;
	}
	return tw;
}

Twist random(int step) {
	Twist tw;
	tw.linear.x = (double)(rand() / (double)RAND_MAX);
	tw.angular.z = (double)((rand() / (double)RAND_MAX) - 0.5) * 2;
	return tw;
}