#include <ZumoShield.h>

ZumoMotors motors;

void setup() {
  // put your setup code here, to run once:

}

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
}
