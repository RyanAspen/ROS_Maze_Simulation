This package is meant to hold Gazebo files for the robot simulation and any scripts needed for initializing that simulation.

TODO:
- Create Gazebo file with robot description that responds to Twist commands (Done)
- Add basic world features to Gazebo file (Done)
- Test (Done)
- Create script to generate new Gazebo files with grid worlds (need to modify hyperparameters)

To start up bidirectional communication between ROS and Gazebo for Twist messages, use the following command:

- ros2 run ros_gz_bridge parameter_bridge /cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist

To create new Gazebo files, run
- "g++ -o test create_gazebo.cpp"
- "./test"

The new Gazebo file will be under the gazebo folder.