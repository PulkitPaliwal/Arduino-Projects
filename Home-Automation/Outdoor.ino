#include <Servo.h>

int max_angle=115; //The max angle with which we want to rotate the motor.
                                                                                                            
int ledVolt =A1; 
float Voltage;  
float thresh=300;
int pos = 0;  //initial position of servo

Servo servo_9;  //creating a servo object for upper flick
Servo servo_7;  //creating a servo object for lower flick

void setup()
{
  servo_9.attach(9, 500,  2500 );
  servo_7.attach(7, 500,  2500 );
  pinMode(ledVolt, INPUT);
  Serial.begin(9600);              
}

void loop()
{ 
  
  Voltage= analogRead(ledVolt);
  Serial.println(Voltage);  
      
    if(Voltage>thresh){
      for (pos = 0; pos <= max_angle; pos += 1) {
        servo_9.write(pos);
        delay(1);} 
      
      for (pos = max_angle; pos >= 0; pos -= 1){
        servo_7.write(pos);
         delay(1);}
      }
  
   else{
    for (pos = max_angle; pos >= 0; pos -= 1){
        servo_9.write(pos);
         delay(1);}
    for (pos = 0; pos <= max_angle; pos += 1) {
        servo_7.write(pos);
        delay(1);}
   }  
  
    
  }
