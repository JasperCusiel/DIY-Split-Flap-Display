// Constant Speed Stepper test 

#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::FULL4WIRE, 5, 6, 7, 8); 

void setup()
{  
   stepper.setMaxSpeed(1000);
   stepper.setSpeed(150);	
}

void loop()
{  
   stepper.runSpeed();
}
