#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motors;
ZumoReflectanceSensorArray linesensors(QTR_NO_EMITTER_PIN);
// Specifying QTR_NO_EMITTER_PIN sets the option that we do not want to actively turn the IR emitters on and off. 
// Instead they will be on by default the entire time.
ZumoBuzzer buzzer; // create a buzzer to play sound

void setup(){
 int i;
  int spin_direction = 1;
  motors.setSpeeds(80*spin_direction, -80*spin_direction);
  for(i = 0; i<250; i++){
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
void loop() {
  int line_position = linesensors.readLine(sensor_vals); 
  int frequency = 220 + ((float)line_position / 5000) * 660;// play a tone that gets higher when the line is to the right

  buzzer.playFrequency(frequency, 100, 15);
  while (buzzer.isPlaying()); 
}
/*
void loop() {
  // put your main code here, to run repeatedly:

  // drive for 4 seconds
  motors.setLeftSpeed(100);
  motors.setRightSpeed(100);
  delay(4000); // 4 seconds of delay

  //stop!
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  
  while(true){
  } // so the robot stops after running the loop once!
  
}
*/
