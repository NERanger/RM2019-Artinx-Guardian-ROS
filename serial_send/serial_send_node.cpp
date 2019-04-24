/**
 * @Auther NERanger
 * @Email  11712605@mail.sustech.edu.cn
*/

#include "ros/ros.h"
#include "roborts_msgs/GimbalAngle.h"
#include <serial/serial.h>
#include "serial_send_node.h"

serial::Serial board_serial;
uint8_t output_buffer[OUTPUT_BUFFER_SIZE];
f64_uchar_u gimbal_yaw_angle_f64, gimbal_yaw_angle_uchar, gimbal_pitch_angle_f64, gimbal_pitch_angle_uchar;

void setGimbalControlSerialBuffer(const roborts_msgs::GimbalAngle::ConstPtr& msg, uint8_t *buffer, size_t size);

/**
 *
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void serialSendNodeCallback(const roborts_msgs::GimbalAngle::ConstPtr& msg)
{
  ROS_INFO("gimbal cmd:\nYAW_MODE:[%d]\nPITCH_MODE:[%d]\nYAW_ANGLE:[%f]\nPITCH_ANGLE:[%f]", msg->yaw_mode
                                                                                          , msg->pitch_mode
                                                                                          , msg->yaw_angle
                                                                                          , msg->pitch_angle);

  setGimbalControlSerialBuffer(msg, output_buffer, OUTPUT_BUFFER_SIZE);

  board_serial.write(output_buffer, OUTPUT_BUFFER_SIZE);
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "gimbal_cmd_serial_send_node");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber sub = n.subscribe("/cmd_gimbal_angle", 1000, serialSendNodeCallback);

  try
  {
    board_serial.setPort("/dev/ttyUSB0");
    board_serial.setBaudrate(115200);
    board_serial.setBytesize(serial::eightbits);
    board_serial.setParity(serial::parity_even);
    board_serial.setStopbits(serial::stopbits_one);
    board_serial.setFlowcontrol(serial::flowcontrol_none);
    
    serial::Timeout serialTimeOut = serial::Timeout::simpleTimeout(1000); 
    board_serial.setTimeout(serialTimeOut);

    board_serial.open();
  }
  catch(serial::IOException& e)
  {
    ROS_ERROR_STREAM("Unable to open serial port "); 
    return -1; 
  }
  

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}

void setGimbalControlSerialBuffer(const roborts_msgs::GimbalAngle::ConstPtr& msg, uint8_t *buffer, size_t size)
{
  gimbal_yaw_angle_f64.double_data = msg->yaw_angle;
  gimbal_pitch_angle_f64.double_data = msg->pitch_angle;

  for(int i = 0; i < UNION_UCHAR_SIZE; i++)
  {
    gimbal_yaw_angle_uchar.uchar_data[i] = gimbal_yaw_angle_f64.uchar_data[i];
    gimbal_pitch_angle_uchar.uchar_data[i] = gimbal_pitch_angle_f64.uchar_data[i];
  }

  output_buffer[0] = msg->yaw_mode;
  output_buffer[1] = msg->pitch_mode;

  output_buffer[2] = gimbal_yaw_angle_uchar.uchar_data[0];
  output_buffer[3] = gimbal_yaw_angle_uchar.uchar_data[1];
  output_buffer[4] = gimbal_yaw_angle_uchar.uchar_data[2];
  output_buffer[5] = gimbal_yaw_angle_uchar.uchar_data[3];
  output_buffer[6] = gimbal_yaw_angle_uchar.uchar_data[4];
  output_buffer[7] = gimbal_yaw_angle_uchar.uchar_data[5];
  output_buffer[8] = gimbal_yaw_angle_uchar.uchar_data[6];
  output_buffer[9] = gimbal_yaw_angle_uchar.uchar_data[7];

  output_buffer[10] = gimbal_pitch_angle_uchar.uchar_data[0];
  output_buffer[11] = gimbal_pitch_angle_uchar.uchar_data[1];
  output_buffer[12] = gimbal_pitch_angle_uchar.uchar_data[2];
  output_buffer[13] = gimbal_pitch_angle_uchar.uchar_data[3];
  output_buffer[14] = gimbal_pitch_angle_uchar.uchar_data[4];
  output_buffer[15] = gimbal_pitch_angle_uchar.uchar_data[5];
  output_buffer[16] = gimbal_pitch_angle_uchar.uchar_data[6];
  output_buffer[17] = gimbal_pitch_angle_uchar.uchar_data[7];
}

