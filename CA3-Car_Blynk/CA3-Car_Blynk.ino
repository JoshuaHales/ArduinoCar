#include <SoftwareSerial.h> //Include SoftwareSerial library.
#include <BlynkSimpleStream.h> //Include Blynk library. 
#include <AFMotor.h> //Include Motor-shield library.
#define BLYNK_PRINT DebugSerial //Defining Blynk serial.
#define trigPin 12 //Defining transmitter pin of sensor. 
#define echoPin 11 //Defining receiver pin of sensor.

SoftwareSerial DebugSerial(2, 3); //Declaring RX, TX pins.
AF_DCMotor motor1(2, MOTOR12_8KHZ); //Declaring motor 1 on 8KHz.
AF_DCMotor motor2(4, MOTOR12_1KHZ); //Declaring motor 2 on 1KHz.
char auth[] = "30b8e345f884471d800b06d32df4a10f"; //Declaring authentication code for Blynk.
boolean motorState = false; //Declaring intial moterstate value.
int startCount = 0; //Declaring intial startCount value.
 
void setup() { //Setup of initial variables.
  DebugSerial.begin(9600); //Initialize serial debug at 9600 bits per second.
  Serial.begin(9600); //Initialize serial communication at 9600 bits per second.
  Blynk.begin(Serial, auth); //Start Blynk communication.
  Serial.println("Starting motor"); //Outputing message in serial.
  pinMode(trigPin, OUTPUT); //Set the trig pin to output (Send sound waves).
  pinMode(echoPin, INPUT); //Set the echo pin to input (recieve sound waves).
  motor1.setSpeed(105); //set the speed of the motors, between 0-255.
  motor2.setSpeed (135); //set the speed of the motors, between 0-255.
  pinMode(LED_BUILTIN, OUTPUT); //Set the LED pin.
}
 
void loop() { //Looping through elements.
  Blynk.run(); //Running Blynk functions.
  if (motorState == true){ //Check if motorState has been set to true.
    motor1.setSpeed(105); //set the speed of the motors, between 0-255.
    motor2.setSpeed (135);
    startCount = 1; //Set startCount to 11.
    long duration, distance; //Declaring duration and distance values (Starting sensor scan).
    digitalWrite(trigPin, LOW); //Turn off scan.  
    delayMicroseconds(2); //Delay 2ms.
    digitalWrite(trigPin, HIGH); //Turn On scan. 
    delayMicroseconds(10); //Delay 10ms.
    digitalWrite(trigPin, LOW); //Turn off scan.  
    duration = pulseIn(echoPin, HIGH); //Time to return values to sensor.
    distance = (duration/2) / 29.1; //Convert the distance to centimeters.
    
    if (distance < 15) { //If there's an obstacle 15 centimers, ahead, do the following:
      Serial.print ("Distance From Car is: "); //Outputing message in serial.
      Serial.print (distance); //Outputing message in serial.
      Serial.print (" CM!"); //Outputing message in serial.
      Serial.println (" Turning!"); //Outputing message in serial.
      motor1.run(FORWARD); //Turn car as long as there's an obstacle ahead.
      motor2.run (BACKWARD); //Reverse wheel.
      digitalWrite(LED_BUILTIN, HIGH); //Turn on LED.
    }
  
    if (distance > 15){ //If there's no obstacle 15 centimers, ahead, do the following:
       Serial.println ("No obstacle detected. going forward"); //Outputing message in serial.
       delay (15); //Delay 15ms.
       motor1.run(FORWARD); //If there's no obstacle ahead, go Forward. 
       motor2.run(FORWARD); //Wheel foward.
       digitalWrite(LED_BUILTIN, LOW); //Turn off LED.
    } 
  }
}  
 
/* AUTO MODE */
BLYNK_WRITE(V1)  //Button attached to Virtual Pin 1 in SWITCH mode.
{
  int i = param.asInt(); //Declaring button value from Blynk.
  if(i == 1){ //If button value equals 1.
    motorState = true; //Set to true.
  }
  else{ //If button value equals 0.
    motorState = false; //Set to false.   
    motor1.run(RELEASE); //If there's no obstacle ahead, go Forward. 
    motor2.run(RELEASE); //Wheel foward.
  }
}

/* GO STRAIGHT */
BLYNK_WRITE(V2)  //Button attached to Virtual Pin 2 in SWITCH mode.
{
  int i = param.asInt(); //Declaring button value from Blynk.
  if(i == 1){ //If button value equals 1.
    motor1.run(FORWARD); //If there's no obstacle ahead, go Forward. 
    motor2.run(FORWARD); //Wheel foward.
  }
  else{ //If button value equals 0.   
    motor1.run(RELEASE); //If there's no obstacle ahead, go Forward. 
    motor2.run(RELEASE); //Wheel foward.
  }
}

/* TURN RIGHT */
BLYNK_WRITE(V3)  //Button attached to Virtual Pin 3 in SWITCH mode.
{
  int i = param.asInt(); //Declaring button value from Blynk.
  if(i == 1){ //If button value equals 1.
    motor1.run(FORWARD); //Turn car as long as there's an obstacle ahead.
    motor2.run (BACKWARD); //Reverse wheel.
  }
  else{ //If button value equals 0.  
    motor1.run(RELEASE); //If there's no obstacle ahead, go Forward. 
    motor2.run(RELEASE); //Wheel foward.
  }
}

/* REVERSE */
BLYNK_WRITE(V4)  //Button attached to Virtual Pin 4 in SWITCH mode.
{
  int i = param.asInt(); //Declaring button value from Blynk.
  if(i == 1){ //If button value equals 1.
    motor1.run(BACKWARD); //Turn car as long as there's an obstacle ahead.
    motor2.run (BACKWARD); //Reverse wheel.
  }
  else{ //If button value equals 0. 
    motor1.run(RELEASE); //If there's no obstacle ahead, go Forward. 
    motor2.run(RELEASE); //Wheel foward.
  }
}

/* TURN LEFT */
BLYNK_WRITE(V5)  //Button attached to Virtual Pin 5 in SWITCH mode.
{
  int i = param.asInt(); //Declaring button value from Blynk.
  if(i == 1){ //If button value equals 1. 
    motor1.run(BACKWARD); //Turn car as long as there's an obstacle ahead.
    motor2.run (FORWARD); //Reverse wheel.
  }
  else{ //If button value equals 0.  
    motor1.run(RELEASE); //If there's no obstacle ahead, go Forward. 
    motor2.run(RELEASE); //Wheel foward.
  }
}

