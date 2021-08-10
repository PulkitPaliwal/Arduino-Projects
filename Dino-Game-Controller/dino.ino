#include <Servo.h>

int max_angle=115; //The angle with which we want to rotate the motor.

int measured_average=160; //Measured average of voltage of black and white screen (check using values printed on serial monitor)
                                                                                                            
int ledVolt =A1; //Pin at which we measure the voltage 

float Voltage;  //Variable that stores the value of voltage measured at A1

int pos = 0;  //initial position of servo

Servo servo_9;  //creating a servo object

const int max_iter=500; //number of iterations after which the loop 'resets', do not keep max_iter>1200 since it can lead to an error due to insufficient memory

bool hit[max_iter];  //creating an array to store whether the spacebar was hit on a particular iteration

int i=0; 
int j=0;
int l=0; 
   
bool prev[3]; //creating an array to store whether the spacebar was hit in the previous three iterations


void setup()
{
  servo_9.attach(9, 500,  2500 );
  pinMode(ledVolt, INPUT);
  Serial.begin(9600);

  //initializaing the previous three hit array to false
  
  while(j<3){
    prev[j]=0;
    j++;
  }          

  //initializing array to false
  
  while(l<max_iter){
    hit[l]=0;
    l++;
  }                          
}

//creating a function to call whenever the spacebar needs to be pressed

void pressSpace(){
  for (pos = 0; pos <= max_angle; pos += 1) {
        // tell servo to go to position in variable 'pos'
        servo_9.write(pos);
        delay(1);}
     
        for (pos = max_angle; pos >= 0; pos -= 1) {
        // tell servo to go to position in variable 'pos'
        servo_9.write(pos);
        // wait 1 ms for servo to reach the position
        // Wait for 1 millisecond(s)
         delay(1);}
  }
  
  int hit_curr=0; //initialize the number of hits to zero
  int hit_rec_prev=0; // initialize the number of hits in previous level to 0
  float dtime=0.8; /*create and initialize a delay time variable which is optimized 
  for scores upto 100 and then starts to decrease as the levels go up */
  float reduction_factor=1.15; //the factor with which the dtime falls when the levels advance
  
void loop()
{ 
  
  Voltage= analogRead(ledVolt);
  Serial.println(Voltage); 
  delay(dtime*1.1);

  /* In a practical project
  the rotation of motor may be accompanied by a 
  voltage turbulence of the entire arduino board
  and since we rely on the measured voltage to 
  decide whether the motor should be rotated or
  not, it becomes essential that the motor is not
  rotated in two or maybe three simultaneous iterations.
  */

  
  if( !prev[0] && !prev[1] && !prev[2]){
      
    if(Voltage<measured_average){
      pressSpace();
      hit[i]=true; hit_curr++;             
      }
      
     delay(dtime);
  }

  //change the dtime
  if(hit_curr==hit_rec_prev+9){
    hit_rec_prev=hit_curr; 
    dtime=dtime/reduction_factor;
    }

  //update prev array
  prev[2]=prev[1];
  prev[1]=prev[0];
  prev[0]=hit[i];

  //update the value of i
  i++;

  //accomodate i>max_iter case so that the hit array does not go out of index
  if(i>max_iter){i=0;}
}
