# Part A

## Author

| Name                | Student ID | CodicePersona | Academic e-mail address            |
|:------------------- |:----------:|:-------------:|:---------------------------------- |
| Circhetta Francesco | 843324     | 10496325      | francesco.circhetta@mail.polimi.it |

## How-To

### Environment

In order to run this project you should have a *working* `ros-kinetic-desktop-full` and `gazebo7` installation.

A catkin workspace should have already been created (probably in `~/catkin_ws`) and `catkin_make` launched for the first time to populate the workspace.

You also need to install a package, if you want to control the robot:

```
$  sudo apt install ros-kinetic-turtlebot3-teleop
```

### Build

Copy the `first_project` directory into the `src` folder of your catkin workspace. Then open a terminal and run this command in the workspace root:

```
$ catkin_make
```

It should terminate without any error.

### Run

Open a terminal and start roscore:

```
$ roscore
```

Open another terminal, source the catkin workspace and launch the gazebo simulation:

```
$ source ~/catkin_ws/devel/setup.bash
$ roslaunch first_project first_project.launch
```

Launch the `turtlebot3_teleop` node to control the robot:

```
$ roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
```

### Play

Using your keyboard w/a/s/d/x keys, move around with the robot in the Gazebo world. As you move, you should see some lines coming in the terminal where you launched the simulation (at 20.0Hz).

```
[ INFO] [1525262269.985960945, 58.600000000]: WheelEncoder(ns = assembly5/): left wheel speed =  0.0000 rad/s, right wheel speed = -0.0000 rad/s.
[ INFO] [1525262270.036393307, 58.650000000]: WheelEncoder(ns = assembly5/): left wheel speed = -0.0000 rad/s, right wheel speed = -0.0000 rad/s.
[ INFO] [1525262270.087362523, 58.700000000]: WheelEncoder(ns = assembly5/): left wheel speed =  0.0058 rad/s, right wheel speed =  0.0050 rad/s.
```

That's the encoder plugin!

## Bonus

### Topic

The encoder plugin does not only print to the console the left and right wheel rotation speed, but it publishes this data also on a topic.

To see what is being published, use rostopic:

```
$ rostopic echo /assembly5/wheel_encoder
```

### Eye candy

The robot is approximated in its collision structure as a box with two cilinders as wheels and two spheres as casters. Nevertheless, its visual is the original STL rendering and the wheels actually rotate, to please the eyes during the simulation!
