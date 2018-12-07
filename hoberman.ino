#include <Servo.h>

/////Servo Setup//////

Servo myservo;

int servo_lower_bound = 35;
int servo_upper_bound = 135;


//////Microphone Setup/////////
// selecting the analog input pin
const int inputPin = A0;
// size of the window
const int inputWindow = 100;
// placeholder for a single measurement
unsigned int inputSample;

int audio_lower_bound = 0;
int audio_upper_bound = 200;

int diff = 0;

void setup() {
  // initializing the analog input
  pinMode(inputPin, INPUT);
  // initializing the serial communication
  Serial.begin(9600);
  myservo.attach(9);
//  myservo.write(servo_lower_bound);
}

void loop() {

  // two variables for minimum and maximum values in window
  unsigned int inputMax = 0;
  unsigned int inputMin = 1024;

  // loop for the window
  for (unsigned int i = 0; i < inputWindow; i++) {
    // read in a single value
    inputSample = analogRead(inputPin);
    // get the minimum and maximum value
    inputMin = min(inputMin, inputSample);
    inputMax = max(inputMax, inputSample);
  }
  
    diff = diff * 0.9 + (inputMax - inputMin) * 0.1;
//    diff = (inputMax - inputMin);
  
  // send the values on serial
  Serial.print("  Diff: ");
  Serial.print(diff);
  Serial.println();
  
  
  int pos = map(diff, audio_lower_bound, audio_upper_bound, servo_lower_bound, servo_upper_bound);  
  
  Serial.print("  Pos: ");
  Serial.println(pos);
  
  myservo.write(pos);
}
