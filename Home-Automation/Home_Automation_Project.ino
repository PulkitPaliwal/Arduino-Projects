#include "Variables.h"
#include <Servo.h>
#include "DHT.h"

DHT dht(DHTPIN, DHTTYPE);
long int count=0;
Servo SERVO_LAMP_LOWER;
Servo SERVO_LAMP_UPPER;

void initMotor(int activationPin, int pin1, int pin2)
{
    pinMode(activationPin, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    digitalWrite(activationPin, HIGH); 
}

void runMotor(int pin1, int pin2, bool clockwise = true)
{
    if (clockwise) {
       
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    } else {
     
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
    }
}

int inches = 0;

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
  
}


void setup(){
 initMotor(PIN_ACTIVATE_1_2, PIN_INPUT_1, PIN_INPUT_2); //setup front dc motor
 initMotor(PIN_ACTIVATE_3_4, PIN_INPUT_3, PIN_INPUT_4); //setup rear dc motor
 SERVO_LAMP_LOWER.attach(SERVO_LAMP_OFF_PIN);   //setup rear servo
 SERVO_LAMP_UPPER.attach(SERVO_LAMP_ON_PIN); //setup forward servo
 Serial.begin(9600);     
 pinMode(13, OUTPUT);
 dht.begin();
 Serial.print("Hi there! \n To turn on the lamp, press 1, to turn it off press 2. \n To roll up the current, press U, to roll down the curtain, press U. \n To test funtionality, press T. ");
 }

void turn_on_the_fan(){
    
}

void loop(){
   while(Serial.available()){
    { 
      char inChar = Serial.read(); 
      inputString = inChar;        
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }   
  
    /*
     * Here I have setup two motors to roll down a twin roller curtain using a DC motor
     * The motors should rotate clockwise while pulling the curtain up, and anti-clockwise will closing the curtain
     */
    if(inputString == "U"){ //Pull up the curtain

        if(0.01723 * readUltrasonicDistance(7, 7)<190){
        runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
        runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
        //digitalWrite(13, HIGH); 
        }
    }
    
    if(inputString == "D"){ //Roll down the curtain until its 30cm from the floor
       
       if(0.01723 * readUltrasonicDistance(7, 7)>30){
          runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
          runMotor(PIN_INPUT_3, PIN_INPUT_4, false); 
          //digitalWrite(13, LOW);
      }
    }

    /* Setting up lamp off and on
     * If we need to flick the switch to on position the motors should move such that the lower motor should press in on the switch,
       while the upper motor's arm should move away.
     * Similarly upper motor should press the switch while lower motor's arm moves away when flicking the switch to off position
     * Keep in mind that the two processes do not occur simultaneously, hence the moving away operation should occur first   
     * Adjust the angle_max to your needs
    */
    if(inputString == "1"){   
        for(int i=angle_max;i>0 ;i--) {SERVO_LAMP_UPPER.write(i); delay(1);}
        for(int i=0; i<=angle_max;i++) {SERVO_LAMP_LOWER.write(i); delay(1);}
        //digitalWrite(13, HIGH);
    }
    if(inputString == "2"){
       for(int i=angle_max;i>0 ;i--) {SERVO_LAMP_LOWER.write(i); delay(1);}   
       for(int i=0; i<=angle_max;i++) {SERVO_LAMP_UPPER.write(i); delay(1);}
       //digitalWrite(13, LOW);
    }
    
    /* Now we'll create another functionality:
     * The fan should automatically turn on (speed needs to be controlled manually) if  
       the temperature of the room rises above 25 degrees.
     * Currently working this out
     */
    /*if(dht.readTemperature()>25){
       turn_on_the_fan();  
    }*/
    if(){
       serial.print("Temperature:");
       serial.println(dht.readTemperature());
       serial.print("Humidity:");  
       serial.println(dht.readHumidity());
    }
    
    if(inputString == "T"){
       Serial.print("Device is Functional. Is the LED blinking?");
       for(int b=0; b<15; b++){
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
       }
    }
    inputString = "";
    }
  }
