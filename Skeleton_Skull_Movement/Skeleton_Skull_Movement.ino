/* Skeleton Head Code*/

#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards

unsigned long timer;
int head1pos[] = {90,  0,45,135,90,180, 0}; //Head location using degrees
int head1spd[] = { 0,100, 0, 50, 0,80,10}; //The higher the number, the slower the head will move (80 is slow enough)
int x; // initialize the counter for the arrays
int y; // initialize the counter for the movement
int pos1; // mark starting position of the servo
int pos2; // mark the ending positiong of the servo
int currposition; // used to determine where the head is
int degreestomove; // used to determine how many degrees to move from current postion to new position
int direction; // used to determine the direction by making this a postive or negative number
int elements; // to store the number of elements
int speed; // used to store the delay value
unsigned long counter1; //Used to count milliseconds
unsigned long millisnow; //Used to store current milliseconds

void setup() {
  Serial.begin(9600); // open the serial port at 9600 baud for debugging
  servo1.attach(4);  // attaches the servo on pin 9 to the servo object
  elements = sizeof(head1pos)/sizeof(head1pos[0]);
  currposition = head1pos[0];
  Serial.print("Number of Head Positions: "); Serial.print(elements); Serial.println();
}

void loop() {
  for (int x = 0; x <= elements; x++){
    Serial.print("X value is : "); Serial.print(x); Serial.println();
    pos1 = head1pos[x];
    speed = head1spd[x];
    if (x == elements){
      Serial.print("End of Array, next position should be 90 : "); Serial.println();
      pos2 = head1pos[0];
      Serial.print("Next head position is: "); Serial.print(pos2); Serial.println();
    } else {
      pos2 = head1pos[x+1];
    }
    if (pos1 > pos2){
      direction = -1;
      degreestomove = pos1 - pos2;
    } else {
      direction = 1;
      degreestomove = pos2 - pos1;
    }
    Serial.print("Degrees to move : "); Serial.print(degreestomove); Serial.println();
    if (speed == 0){
      servo1.write(pos2)
    }else{
      for (int y = 0; y < degreestomove; y++){
        currposition = currposition + direction;
        servo1.write(currposition);
        Serial.print("Current Position: "); Serial.print(currposition); Serial.println();
        delay(speed);
      }
    }
  }
}
