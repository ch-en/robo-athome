// right now, this is just the PD tutorial code. it moves so fast i have to chase it around ; __ ;

#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
ZumoReflectanceSensorArray linesensors(QTR_NO_EMITTER_PIN);
// Specifying QTR_NO_EMITTER_PIN sets the option that we do not want to actively turn the IR emitters on and off. 
// Instead they will be on by default the entire time.

void setup() {
  int i;
  int spin_direction = 1;
  motors.setSpeeds(80*spin_direction, -80*spin_direction);
  for(i = 0; i<100; i++){
    linesensors.calibrate();
    if(i%50 == 25){ // every 50 loops, starting on loop 25...
      spin_direction = -spin_direction;
      motors.setSpeeds(80*spin_direction, -80*spin_direction);
    }
    delay(20);
  }
  motors.setSpeeds(0,0);
  delay(500);
}


// readLine method:
  // aggregates the data across the six sensors and 
  // returns a value from 0-5000 indicating the estimated location of the line. 
  // 0 = the line is all the way to the left of the robot
  // 5000 = the line is all the way to the right of the robot
  // 2500 = the line is centered under the robot.


// For all of these methods we need a way of measuring the error in the position of the robot 
// relative to the line. us the readLine() method to get the error. 
// If the robot is pefectly centered over the line the readLine() method should return 2500. Therefore...

unsigned int sensor_vals[6];
int BASE_SPEED = 200;
double PROPORTION_GAIN = 0.2;
double DERIVATIVE_GAIN = 3;
int last_error = 0;
void loop() {
  int line_position = linesensors.readLine(sensor_vals);
  int error = line_position - 2500;
  int error_change = error - last_error;
  int left_speed = BASE_SPEED + PROPORTION_GAIN * error + DERIVATIVE_GAIN * error_change;
  int right_speed = BASE_SPEED + -PROPORTION_GAIN * error + -DERIVATIVE_GAIN * error_change;
  last_error = error;
  motors.setSpeeds(left_speed, right_speed);
}
