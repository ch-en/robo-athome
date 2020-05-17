#include <ZumoShield.h>

ZumoMotors motors;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // update:
  // drive for 4 seconds on 100 speed only moved ~2 feet, 
  // so i made it run at 150 speed for 6 seconds
  motors.setLeftSpeed(150);
  motors.setRightSpeed(150);
  delay(6000); // 6 seconds of delay

  //stop!
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  
  while(true){
  } // so the robot stops after running the loop once!
  
}
