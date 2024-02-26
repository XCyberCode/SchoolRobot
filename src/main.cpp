// Include framework
#include <Arduino.h>

// Include external libraries
#include <IRremote.hpp>

// Include core components
#include <sysconf.h>
#include <driver/move_control.hpp>
#include <driver/ultrasonic.hpp>

uint8_t robot_speed = DEFAULT_ROBOT_SPEED;

// Define robot movement engine
move_control robot(
  LEFT_MOTOR_SPEED_PIN, 
  LEFT_MOTOR_DIR_PIN, 
  RIGHT_MOTOR_SPEED_PIN, 
  RIGHT_MOTOR_DIR_PIN
);

// Define ultrasonic sensor engine
/* 
ultrasonic_sensor ultrasonic
(
  ULTRASONIC_ECHO_PIN,
  ULTRASONIC_TRIG_PIN
);
*/

void setup() 
{
  // FOR DEBUG PURPOSES ONLY
  Serial.begin(9600);

  // Prepare robot
  robot.begin();

  // Prepare line sensor
  pinMode(LEFT_CHANNEL_SENSOR_PIN, INPUT); // Left channel
  pinMode(RIGHT_CHANNEL_SENSOR_PIN, INPUT); // Right channel

  // Prepare IR receiver
  IrReceiver.begin(IR_RECEIVER_PIN, false);

  // Prepare ultrasonic sensor
  // ultrasonic.begin();

  robot.set_direction(1, 1);
  robot.raw_move(0, 0);
}

void loop() 
{
  if(digitalRead(LEFT_CHANNEL_SENSOR_PIN))
  {
    robot.raw_move(robot_speed, 0);
  }
  else if(digitalRead(RIGHT_CHANNEL_SENSOR_PIN))
  {
    robot.raw_move(0, robot_speed);
  }
  else
  {
    robot.raw_move(robot_speed, robot_speed);
  }

  // IR receiver dispatcher
  if(IrReceiver.decode())
  {
    if(IrReceiver.decodedIRData.address == IR_REMOTE_ADDRESS)
    {
      if(IrReceiver.decodedIRData.command == IR_REMOTE_UP_BTN)
      {
        if(robot_speed < MAX_ROBOT_SPEED)
        {
          robot_speed += 5;
        }
      }
      if(IrReceiver.decodedIRData.command == IR_REMOTE_DOWN_BTN)
      {
        if(robot_speed > MIN_ROBOT_SPEED)
        {
          robot_speed -= 5;
        }
      }
      if(IrReceiver.decodedIRData.command == IR_REMOTE_OK_BTN)
      {
        robot.set_block_state(!robot.get_block_state());
      }
    }
    IrReceiver.resume();
  }
}