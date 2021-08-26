
char junk;
String inputString="";

#include <Servo.h>

//Front Motor
const int PIN_ACTIVATE_3_4 = 2;
const int PIN_INPUT_3 = 3;
const int PIN_INPUT_4 = 4;

//Rear Motor
const int PIN_ACTIVATE_1_2 = 8;
const int PIN_INPUT_1 = 9;
const int PIN_INPUT_2 = 10;

//Servo Motors
const int SERVO_REAR_PIN=5;
const int SERVO_FRONT_PIN=6;
Servo REAR;
Servo FRONT;

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

void setup(){
 initMotor(PIN_ACTIVATE_1_2, PIN_INPUT_1, PIN_INPUT_2); //setup front dc motor
 initMotor(PIN_ACTIVATE_3_4, PIN_INPUT_3, PIN_INPUT_4); //setup rear dc motor
 REAR.attach(SERVO_REAR_PIN);   //setup rear servo
 FRONT.attach(SERVO_FRONT_PIN); //setup forward servo
 Serial.begin(9600);     
 pinMode(13, OUTPUT)    ;          
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
    if(inputString == "M"){         
        runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
        runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
        //digitalWrite(13, HIGH);
    }
    if(inputString == "S"){   
       digitalWrite(PIN_INPUT_1, LOW);
       digitalWrite(PIN_INPUT_2, LOW);
       digitalWrite(PIN_INPUT_3, LOW);
       digitalWrite(PIN_INPUT_4, LOW);
       //digitalWrite(13, LOW);
    }
    if(inputString == "r"){   
       runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
       //digitalWrite(13, HIGH);
    }
    if(inputString == "f"){
       runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
       //digitalWrite(13, LOW);
    }
    if(inputString == "1"){   
        for(int i=180;i>0 ;i--) {FRONT.write(i); delay(1);}
        //digitalWrite(13, HIGH);
    }
    if(inputString == "2"){   
       for(int i=0; i<=180;i++) {FRONT.write(i); delay(1);}
       //digitalWrite(13, LOW);
    }
    if(inputString == "3"){   
        for(int i=180;i>0 ;i--) {REAR.write(i); delay(1);}
        //digitalWrite(13, HIGH);
    }
    if(inputString == "4"){   
       for(int i=0; i<=180;i++) {REAR.write(i); delay(1);}
       //digitalWrite(13, LOW);
    }
    if(inputString== "z"){
       runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
       //digitalWrite(13, HIGH);
    }
    if(inputString == "x"){
       runMotor(PIN_INPUT_1, PIN_INPUT_2, false); 
       //digitalWrite(13, LOW);
    }
    inputString = "";
  }
  }

