#pragma once

#include <ros/ros.h>

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo_plugins/gazebo_ros_utils.h>

#include <first_project/WheelEncoder.h>

namespace gazebo {
  class GazeboRosWheelEncoder : public ModelPlugin {
  public:
    GazeboRosWheelEncoder();
    virtual ~GazeboRosWheelEncoder();

  protected:
    void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
    void Update(const ros::TimerEvent &event);

  private:
    ros::NodeHandle node_handle_;
    ros::Publisher encoder_publisher_;
    ros::Timer timer;

    first_project::WheelEncoder encoder_;

    GazeboRosPtr gazebo_ros_;
    physics::ModelPtr parent;
    physics::WorldPtr world;

    std::vector<physics::JointPtr> joints_;

    double update_rate_;
  };
}
