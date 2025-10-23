/*
  Tombstone Project.
  Controls the tombstone bell, lid and hand
  by Luis Melo
 */
 int bellrings = 5; //How many times to ring the bell each cycle
 int timer = 1000; //timer variable
 int action = 1; //action variable
 int BELL = 8; //Set Pin 10 for Bell Sound
 int LIDUP = 9; //Set Pin 8 for LID UP
 int HAND = 10; //Set Pin 11 for Hand Action
 int LIDDOWN = 11; //Set Pin 9 for LID DOWN
 int HAND_PROBABILITY = 45; //Use this variable to setup a percentage of time when the hand comes out (45 = 45% chance)

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins 13 as outputs.
  pinMode(LIDUP, OUTPUT);
  pinMode(LIDDOWN, OUTPUT);
  pinMode(BELL, OUTPUT);
  pinMode(HAND, OUTPUT);

  // initialize random seed
  randomSeed(analogRead(0));
}

// the loop function runs over and over again forever
void loop() {
  BellSound();
  delay(3000); // Wait three second to start lifting lid
  TombLid(LIDUP); // Tell Lid to Lift Up
  timer = random(4000) + 1000; // set timer to 1 to 5 seconds
  delay(timer); // Wait (timer) seconds for lid before activating hand
  HandAction(); // Start Hand
  delay(1000); // wait for a second before lowering the lid
  TombLid(LIDDOWN); // Tell Lid to Lower
  timer = random(25000) + 5000;
  // timer = 2000;
  delay(timer); // wait between 5 and 20 seconds before starting all over
}

void TombLid(int direction){
  digitalWrite(direction, HIGH); // Move Lid in Direction Directed
  timer = 4000; // Wait 4 seconds for lid to Finish Moving
  delay(timer);
  digitalWrite(direction, LOW); // Shut off power
}

void BellSound(){
  for (int i = 0; i <= bellrings; i++){
    digitalWrite(BELL, HIGH);
    delay(50);
    digitalWrite(BELL, LOW);
    delay(50);
  }
}

void HandAction(){
  action = random(100);
  if (action < HAND_PROBABILITY){
    digitalWrite(HAND, HIGH);
  }
  delay(3000);
  digitalWrite(HAND, LOW);
  delay(500);
}