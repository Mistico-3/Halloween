/*  Screaming Skull Code version 3.0  by Luis Melo
This code works with a remote control with two buttons.
Button 1 is used to open and close the doors independently
Button 2 is used to lauch the skull
 v1.0 - Initial code
 v2.0 - Changed the code to pulse voltage to actuators since low voltage made them weak and did not work
 v3.0 - Linear actuators are not really going to work so we have changed them with Servo Motors and the code was
        changed to accomodate that
        Also, the eyes will now light up immediately upon opening the doors instead of waiting for the second button to be pressed.
 */
   
#include <SoftwareSerial.h>
#include <Adafruit_Soundboard.h>
#include <Servo.h>
   
#define SFX_TX 12
#define SFX_RX 4
#define SFX_RST 13
   
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

Servo leftdoor;  // create servo object to control left door
Servo rightdoor;  // create servo object to control right door
   
int ACTIVATE_DOORS = 2; // This pin will be an input
int ACTIVATE_SKULL = 3; // This pin will be an input
// int DOORSOPEN = 5; Was used for linear actuators
// int DOORSCLOSE = 6; Was used for linear actuators
int LIGHTEYES = 7;
int LAUNCHSKULL = 8;
int DOORSPEED = 255; //Set from 1 to 255 to control voltage
int door_action = LOW;
int doors_state = 0;
int skull_action = 0;
int skull_state = 0;
int check_doors = 0;
int leftdoorpos = 180; // variable to store servo 1 position
int rightdoorpos = 0; // variable to store servo 2 position
int skulleyestimer;
int millisnow;
int i;
int ii;

void setup(){
  Serial.begin(9600); // open the serial port at 9600 baud for debugging
  ss.begin(9600);  // used to communicate with the sound board
  pinMode(ACTIVATE_DOORS, INPUT_PULLUP); // sets the pin to input using the built-in resistor so it is HIGH by default
  pinMode(ACTIVATE_SKULL, INPUT_PULLUP);  // sets the pin to input using the built-in resistor so it is HIGH by default
  pinMode(LIGHTEYES, OUTPUT);
  pinMode(LAUNCHSKULL, OUTPUT);
  leftdoor.attach(5);  // attaches the left door servo on pin 5 to the servo object
  rightdoor.attach(6);  // attaches the right door servo on pin 6 to the servo object
  leftdoor.write(leftdoorpos);  // Close the left door if it is opened
  rightdoor.write(rightdoorpos);  // Close the right door if it is opened
}

// the loop function runs over and over again forever
void loop(){  
  door_action = digitalRead(ACTIVATE_DOORS); // See if the doors need to be activated by checking if the button is pushed
  if (door_action == LOW){ // If the button is pushed, activate doors
    if (skull_state == 0){ // Check that the skull is not out before proceeding. If it is out, do not activate the doors
      ActivateDoors(); // Activate Doors
    }
  }  
  skull_action = digitalRead(ACTIVATE_SKULL); // Check if the skull needs to be launched
  if (skull_action  == LOW){
    if (skull_state == 1){ //if skull is out, return it
      digitalWrite(LAUNCHSKULL, LOW);
      delay(4000);
      ActivateDoors();
      skull_state = 0;
    }else{
      if (doors_state == 0){
        ActivateDoors();
        digitalWrite(LIGHTEYES, HIGH);
        delay(2000);
      }      
      sfx.playTrack("SCREAM  OGG");
      digitalWrite(LAUNCHSKULL, HIGH);
      digitalWrite(LIGHTEYES, LOW);
      delay(2000);
      skull_state = 1;
    }
  }
  millisnow = millis();
  if (millisnow > skulleyestimer){
    digitalWrite(LIGHTEYES, LOW);
  }
}
   
void ActivateDoors(){
  if (doors_state == 0){
    sfx.playTrack("DOOROPENOGG");
    ii = 0;
    for (int i = leftdoorpos; i >= rightdoorpos; i -= 1){
      ii = ii + 1;
      leftdoor.write(i);
      rightdoor.write(ii);
      Serial.print("Left Door: ");
      Serial.print(i);
      Serial.print(" - Right Door: ");
      Serial.print(ii);
      Serial.println();
      delay(30);
    }
    doors_state = 1;
    skulleyestimer = millis() + 10000;
    digitalWrite(LIGHTEYES, HIGH);
  }else{
    sfx.playTrack("DOORCLSEOGG");
    digitalWrite(LIGHTEYES, LOW);
    for (int i = rightdoorpos; i <= leftdoorpos; i += 1){
      ii = leftdoorpos - i;
      leftdoor.write(i);
      rightdoor.write(ii);
      Serial.print("Left Door: ");
      Serial.print(i);
      Serial.print(" - Right Door: ");
      Serial.print(ii);
      Serial.println();
      delay(30);
    }
    doors_state = 0;
  }
}
