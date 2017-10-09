  #include <LiquidCrystal.h> //Load Liquid Crystal Library 

  #define I1 2  // Control pin 1 for motor 1
  #define I2 3  // Control pin 2 for motor 1
  #define I3 5  // Control pin 1 for motor 2
  #define I4 4  // Control pin 2 for motor 2
  
LiquidCrystal LCD(11, 10, 9, 8, 7, 6);  //Create Liquid Crystal Object called LCD
 
int trigPin=13; //Sensor Trip pin connected to Arduino pin 13
int echoPin=12;  //Sensor Echo pin connected to Arduino pin 11
int myCounter=0;  //declare your variable myCounter and set to 0
int servoControlPin=6; //Servo control line is connected to pin 6
float pingTime;  //time for ping to travel from sensor to target and return
float targetDistance; //Distance to Target in inches
float speedOfSound=1250; //Speed of sound in Km per hour when temp is 77 degrees.
 
void setup() {
  
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(I1, OUTPUT);
pinMode(I2, OUTPUT);
pinMode(I3, OUTPUT);
pinMode(I4, OUTPUT);
LCD.begin(16,2); //Tell Arduino to start your 16 column 2 row LCD
LCD.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
LCD.print("Target Distance:");  //Print Message on First Row
}

// Move forward
void forward() {
  // Move left motor forwaard
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);

  // Move right motor forward
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
}

// Turn 
void turn() {
  // Move left motor backward
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);

  //Move right motor backward
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);

  delay(250);

  // Stop left motor
  digitalWrite(I1, HIGH);
  digitalWrite(I2, HIGH);

  // Move right motor forward in order to turn
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);

  delay(125);
}
 
void loop() {
  
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state
  
  pingTime = pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  targetDistance= speedOfSound * pingTime;  //This will be in Km, since speed of sound was Km per hour
  targetDistance=targetDistance/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  targetDistance= targetDistance*100000;    //Convert Km to cm by multipling by 100000 (cm per Km)
  
  LCD.setCursor(0,1);  //Set cursor to first column of second row
  LCD.print("                "); //Print blanks to clear the row
  LCD.setCursor(0,1);   //Set Cursor again to first column of second row
  LCD.print(targetDistance); //Print measured distance
  LCD.print(" cm");  //Print your units.

// Check if there's an object ahead
  if (targetDistance > 30) {
    // If there's no object ahead, move forward
    forward();
  } else {
    // I there is an object, turn
    turn();
  }
  delay(250); //pause to let things settle  
}  

