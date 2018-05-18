#include <AFMotor.h> //Include Motor-shield library.
#define trigPin 12 //Defining transmitter pin of sensor. 
#define echoPin 11 //Defining receiver pin of sensor.

AF_DCMotor motor1(2, MOTOR12_8KHZ); //Declaring motor 1 on 8KHz.
AF_DCMotor motor2(4, MOTOR12_1KHZ); //Declaring motor 2 on 1KHz.
 
void setup() { //Setup of initial variables.
  Serial.begin(9600); //Initialize serial communication at 9600 bits per second.
  Serial.println("Starting motor"); //Outputing message in serial.
  pinMode(trigPin, OUTPUT); //Set the trig pin to output (Send sound waves).
  pinMode(echoPin, INPUT); //Set the echo pin to input (recieve sound waves).
  motor1.setSpeed(105); //set the speed of the motors, between 0-255.
  motor2.setSpeed (135); //set the speed of the motors, between 0-255.
  pinMode(LED_BUILTIN, OUTPUT); //Set the LED pin.
}
 
void loop() { //Looping through elements.
  long duration, distance; //Declaring duration and distance values (Starting sensor scan).
  digitalWrite(trigPin, LOW); //Turn off scan.    
  delayMicroseconds(2); //Delay 2ms.
  digitalWrite(trigPin, HIGH); //Turn On scan.
  delayMicroseconds(10); //Delay 10ms.
  digitalWrite(trigPin, LOW); //Turn off scan.  
  duration = pulseIn(echoPin, HIGH); //Time to return values to sensor.
  distance = (duration/2) / 29.1;// convert the distance to centimeters.
  
  if (distance < 15) { //If there's an obstacle 15 centimers, ahead, do the following:
    Serial.print ("Distance From Car is: "); //Outputing message in serial.
    Serial.print (distance); //Outputing message in serial.
    Serial.print (" CM!"); //Outputing message in serial.
    Serial.println (" Turning!"); //Outputing message in serial.
    motor1.run(FORWARD);  // Turn as long as there's an obstacle ahead.
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
  
