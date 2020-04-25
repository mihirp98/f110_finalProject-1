#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <tf2_ros/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include <Eigen/Sparse>
#include "OsqpEigen/OsqpEigen.h"

using namespace Eigen;
using namespace std;

//state and input variables
const int nx = 3; //state variables
const int nu = 2; //input variables

class MPC{

public:
    MPC(ros::NodeHandle &nh);
    virtual ~MPC();

private:
	ros::NodeHandle nh_;

	vector<Vector3d> trajectory_ref_;

public:

	void get_params(ros::NodeHandle& nh);
	void get_reference_traj();
	void propagate_Dynamics(Eigen::VectorXd& state(nx), Eigen::VectorXd& input(nu), Eigen::VectorXd& next_state(nx), double dt);
	void get_linear_dynamics(Matrix<double,nx,nx>& Ad, Matrix<double,nx, nu>& Bd, Matrix<double,nx,1>& hd, Matrix<double,nx,1>& x_op, Matrix<double,nu,1>& u_op);
	void get_MPC_path();
	void publish_MPC_path();
	void visualize_MPC();

};


