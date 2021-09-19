#include <AccelStepper.h>
#include <math.h>

const char *letters[] = {" ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0","1", "2", "3", "4", "5", "6", "7", "8", "9","!","#", ","};
                           
int positions[] = {0, 52, 104, 156, 208, 260, 312, 364, 416, 475, 520, 572, 624, 676, 728, 780, 832, 884, 946, 988, 1050, 1102, 1144, 1196, 1248, 1300, 1362, 1402, 1456, 1508, 1560, 1612, 1664, 1726, 1768, 1820, 1872, 1924, 1976, 2028};
int num = -51.2;
const char *to_find;
int len = (sizeof (letters) / sizeof (*letters));
int x;
char buffer[128];
String inData;
int stepperPos;
int index;
float numSteps = 0;

#define CMDBUFFER_SIZE 32
#define FULLSTEP 4

int motorPin1 = 9; 
int motorPin2 = 10; 
int motorPin3 = 11; 
int motorPin4 = 12; 

AccelStepper stepper(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  Serial.begin(9600);
  //for (int i=0; i<41; i++) {
    //positions[i] = ((num += 52));
    //Serial.println(positions[i]);
 //}
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(10000);
  stepper.setSpeed(1000);
  homeDisplay();
   
}


void loop() {
  moveStepper();
  serialIn();
  }

void serialIn() {
  static char cmdBuffer[CMDBUFFER_SIZE] = "";
  char c;
  if(Serial.available() > 0) {
    c = processCharInput(cmdBuffer, Serial.read());
    if (c == '\n') {
      getLetterIndex(cmdBuffer);
      Serial.println("Letter: "+ String(cmdBuffer));
      cmdBuffer[0] = 0;
    }      
  }
}

void homeDisplay() {
  int sensorPin = A6;
  int sensorValue = 500;
  pinMode(sensorPin, INPUT_PULLUP);
  stepper.setSpeed(700);
  while (sensorValue >= 200) {
    sensorValue = analogRead(sensorPin);
    stepper.runSpeed();
  }
  stepper.setCurrentPosition(52);
  Serial.println("Module Homed");
}


void getPositionByIndex(int index) {
  Serial.println("Position: " + String(positions[index]));
  if (int(positions[index]) == 0 and stepper.currentPosition() == 2048) {
    stepper.moveTo(2100);
    stepper.setCurrentPosition(0);
  }
  
  else if (int(positions[index]) < stepper.currentPosition()) {
    stepper.moveTo(2048);
    moveStepper();
    stepper.setCurrentPosition(0);
    stepper.moveTo(int(positions[index]));
  }
  else {
    stepper.moveTo(positions[index]);
  }
  
}

void moveStepper() {
  while (stepper.distanceToGo() > 0) {
    stepper.run(); 
  }
  stepper.disableOutputs();
}

void getLetterIndex(const char *letter) {
  for (x = 0; x < len; x++) {
    if (strcmp (letter, letters[x]) == 0) {
      getPositionByIndex(x);
    } 
  }
}

char processCharInput(char* cmdBuffer, const char c) {
  if (c >= 32 && c <= 126) {
    if (strlen(cmdBuffer) < CMDBUFFER_SIZE) { 
      strncat(cmdBuffer, &c, 1);   //Add it to the buffer
    }
    else {   
      return '\n';
    }
  }
  
  else if ((c == 8 || c == 127) && cmdBuffer[0] != 0) {
    cmdBuffer[strlen(cmdBuffer)-1] = 0;
  }
  return c;
}
