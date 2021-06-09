// Copyright 1996-2020 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 * To run gmapping you should start gmapping:
 * rosrun gmapping slam_gmapping scan:=/pioneer3at/Sick_LMS_291/laser_scan/layer0 _xmax:=30 _xmin:=-30 _ymax:=30 _ymin:=-30
 * _delta:=0.2
 */

#include <sensor_msgs/Image.h>
#include <signal.h>
#include <std_msgs/String.h>
#include "ros/ros.h"

#include <webots_ros/set_float.h>
#include <webots_ros/set_int.h>
#include <string>
#include <iostream>

using namespace std;

#define TIME_STEP 32

ros::NodeHandle *n;

static int controllerCount;
static std::vector<std::string> controllerList;

ros::ServiceClient timeStepClient;
webots_ros::set_int timeStepSrv;


// catch names of the controllers availables on ROS network
void controllerNameCallback(const std_msgs::String::ConstPtr &name) {
  controllerCount++;
  controllerList.push_back(name->data);
  ROS_INFO("Controller #%d: %s.", controllerCount, controllerList.back().c_str());
}

void quit(int sig) {
  ROS_INFO("User stopped the 'sensor' node.");
  timeStepSrv.request.value = 0;
  timeStepClient.call(timeStepSrv);
  ros::shutdown();
  exit(0);
}

int main(int argc, char **argv) {
  std::string controllerName;
  // create a node named 'pioneer3at' on ROS network
  ros::init(argc, argv, "sensor", ros::init_options::AnonymousName);
  n = new ros::NodeHandle;

  signal(SIGINT, quit);

  // subscribe to the topic model_name to get the list of availables controllers
  ros::Subscriber nameSub = n->subscribe("model_name", 100, controllerNameCallback);
  while (controllerCount == 0 || controllerCount < nameSub.getNumPublishers()) {
    ros::spinOnce();
    ros::spinOnce();
    ros::spinOnce();
  }
  ros::spinOnce();

  timeStepClient = n->serviceClient<webots_ros::set_int>("sensor0/robot/time_step");
  timeStepSrv.request.value = TIME_STEP;


for(int i=0; i<controllerCount; i++){

  // enable rangefinder
  ros::ServiceClient set_rangefinder_client;
  webots_ros::set_int rangefinder_srv;

  set_rangefinder_client = n->serviceClient<webots_ros::set_int>( "sensor" + to_string(i) + "/range_finder/enable" );
  rangefinder_srv.request.value = TIME_STEP;
  if (set_rangefinder_client.call(rangefinder_srv) && rangefinder_srv.response.success) {
    ROS_INFO("%s", ("range finder " + to_string(i) + " enabled").c_str());
  } 
  else {
    if (!rangefinder_srv.response.success)
      ROS_ERROR("%s", ("range finder " + to_string(i) + " sampling period is not valid.").c_str());
    ROS_ERROR("%s", ("Failed to enable range finder " + to_string(i)).c_str());
    return 1;
  }

    // enable camera
  ros::ServiceClient set_camera_client;
  webots_ros::set_int camera_srv;

  set_camera_client = n->serviceClient<webots_ros::set_int>("sensor" + to_string(i) + "/camera/enable");
  camera_srv.request.value = TIME_STEP;
  if (set_camera_client.call(camera_srv) && camera_srv.response.success) {
    ROS_INFO("%s", ("camera " + to_string(i) + " enabled").c_str());
  } 
  else {
    if (!camera_srv.response.success)
      ROS_ERROR("%s", ("camera " + to_string(i) + " sampling period is not valid.").c_str());
    ROS_ERROR("%s" , ("Failed to enable camera " + to_string(i)).c_str());
    return 1;
  }
}


// // enable kinect-depth
//   ros::ServiceClient set_rangekinect_client;
//   webots_ros::set_int rangekinect_srv;

//   set_rangekinect_client = n->serviceClient<webots_ros::set_int>("sensor/kinect_range/enable");
//   rangekinect_srv.request.value = TIME_STEP;
//   if (set_rangekinect_client.call(rangekinect_srv) && rangekinect_srv.response.success) {
//     ROS_INFO("range-kinect enabled.");
//   } 
//   else {
//     if (!rangekinect_srv.response.success)
//       ROS_ERROR("range-kinect Sampling period is not valid.");
//     ROS_ERROR("Failed to enable range-kinect.");
//     return 1;
//   }

// // enable kinect-color
//   ros::ServiceClient set_colorkinect_client;
//   webots_ros::set_int colorkinect_srv;

//   set_colorkinect_client = n->serviceClient<webots_ros::set_int>("sensor/kinect_color/enable");
//   colorkinect_srv.request.value = TIME_STEP;
//   if (set_colorkinect_client.call(colorkinect_srv) && colorkinect_srv.response.success) {
//     ROS_INFO("color-kinect enabled.");
//   } 
//   else {
//     if (!colorkinect_srv.response.success)
//       ROS_ERROR("color-kinect Sampling period is not valid.");
//     ROS_ERROR("Failed to enable color-kinect.");
//     return 1;
//   }


  // main loop
  while (ros::ok()) {
    if (!timeStepClient.call(timeStepSrv) || !timeStepSrv.response.success) {
      ROS_ERROR("Failed to call service time_step for next step.");
      break;
    }
    ros::spinOnce();
  }
  timeStepSrv.request.value = 0;
  timeStepClient.call(timeStepSrv);

  ros::shutdown();
  return 0;
}