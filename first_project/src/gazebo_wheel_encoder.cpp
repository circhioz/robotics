#include "first_project/gazebo_wheel_encoder.h"

namespace gazebo {

  enum {
    RIGHT,
    LEFT,
  };

  GazeboRosWheelEncoder::GazeboRosWheelEncoder() {}

  GazeboRosWheelEncoder::~GazeboRosWheelEncoder() {}

  /* Load the controller */
  void GazeboRosWheelEncoder::Load(physics::ModelPtr _parent,
                                   sdf::ElementPtr _sdf) {

    /* Make sure the ROS node for Gazebo has already been initalized */
    if (!ros::isInitialized()) {
      ROS_FATAL("A ROS node for Gazebo has not been initialized, unable to load "
                "plugin.");
      return;
    }

    parent = _parent;
    world = parent->GetWorld();

    gazebo_ros_ = GazeboRosPtr(new GazeboRos(_parent, _sdf, "WheelEncoder"));
    gazebo_ros_->isInitialized();

    /* Get update rate */
    gazebo_ros_->getParameter<double>(update_rate_, "updateRate", 20.0);

    /* Get the required joints */
    joints_.resize(2);
    joints_[LEFT] = gazebo_ros_->getJoint(parent, "leftJoint", "left_joint");
    joints_[RIGHT] = gazebo_ros_->getJoint(parent, "rightJoint", "right_joint");

    /* Publisher */
    encoder_publisher_ = gazebo_ros_->node()->advertise<first_project::WheelEncoder>("wheel_encoder", 100);
    ROS_INFO_NAMED("WheelEncoder",
                   "%s: Advertise wheel_encoder",
                   gazebo_ros_->info());

    /* Set up timer */
    timer = gazebo_ros_->node()->createTimer(ros::Duration(1.0 / update_rate_),
                                             &GazeboRosWheelEncoder::Update, this);
  }

  void GazeboRosWheelEncoder::Update(const ros::TimerEvent &event) {
    ros::Time current_time = ros::Time::now();
    double left_joint_velocity = joints_[LEFT]->GetVelocity(0);
    double right_joint_velocity = joints_[RIGHT]->GetVelocity(0);

    ROS_INFO_NAMED(
                   "WheelEncoder",
                   "%s: left wheel speed = % 7.4f rad/s, right wheel speed = % 7.4f rad/s.",
                   gazebo_ros_->info(),
                   left_joint_velocity,
                   right_joint_velocity);

    encoder_.header.stamp = current_time;
    encoder_.left = left_joint_velocity;
    encoder_.right = right_joint_velocity;

    encoder_publisher_.publish(encoder_);
  }

  GZ_REGISTER_MODEL_PLUGIN(GazeboRosWheelEncoder);
}
