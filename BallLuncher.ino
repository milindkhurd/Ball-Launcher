#include <Servo.h>

// encoder declarations
#define POSITION_SENSOR 2
#define ENCODER_SENSOR 3
#define SPIN_MOTOR 9

enum spin {
   topspin = 0,           
   toprightsidespin = 1,  
   rightsidespin = 2,         
   backrightsidespin = 3, 
   backspin = 4,
   backleftsidespin = 5,
   leftsidespin = 6,
   topleftsidespin = 7
};

enum speedset {
 clockwiseset = 87,
 haltset = 94,
 counterclockwiseset = 100    
};

enum rotation {
  clockwise = 0,
  anticlockwise = 1  
};

int steps = 0;   // steps to move
spin curpos = topspin;
rotation rotate = clockwise;  // direction in which to move c - cw, a - ccw
speedset movement = haltset;    // servo current position
int readByte = 0;

//encoder variables
byte sensorStatusA = 0;
byte sensorStatusB = 0;

void change_position_sensor() {
  sensorStatusA = digitalRead(POSITION_SENSOR);
  if (sensorStatusA == LOW)
    Serial.print("A is low\n");

  if (sensorStatusA == HIGH)
    Serial.print("A is high\n");
}

void change_encoder_sensor(){
  sensorStatusB = digitalRead(ENCODER_SENSOR);
  if (sensorStatusB == LOW)
    Serial.print("B is low\n");

  if (sensorStatusB == HIGH)
    Serial.print("B is high\n");
}


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

  void computeRotation(int curr, int set){
    
    int nextpos = curr;
    int cwsteps, ccwsteps;
    int steps = 0;
      
    while (nextpos != set) {
      nextpos += 1;
      steps += 1;
  
      if (nextpos == 8)
        nextpos = 0;
    }
  
    cwsteps = steps;
    nextpos = curr;
    steps = 0;
  
    while (nextpos != set) {
      nextpos -= 1;
      steps += 1;
  
      if (nextpos == -1)
        nextpos = 7;
    }
  
    ccwsteps = steps;
  
    if (cwsteps <= ccwsteps)
    {
      rotate = clockwise;
      steps = cwsteps;
      Serial.print("rotate clockwise, steps = ");
      Serial.println(steps);
    }
    else
    {
      rotate = anticlockwise;
      steps = ccwsteps;
      Serial.print("rotate anticlockwise, steps = ");
      Serial.println(steps);
    }

}  

void setup() {
  Serial.begin(115200);
  attachInterrupt(0, change_position_sensor, CHANGE);
  attachInterrupt(1, change_encoder_sensor, CHANGE);

  myservo.attach(SPIN_MOTOR);  // attaches the servo on pin 9 to the servo object
  myservo.write(movement);   //98 is stop position, lower value, clockwise
  Serial.print("Servo value = ");
  Serial.println(myservo.read());
}

void loop() {
  
readByte = 0;
  if (Serial.available() > 0){//if we get a valid byte, read from serial:
      //get incoming byte:
      readByte = Serial.read() - '0';
      Serial.println(readByte);   // send a 'r' to initiate next data from computer

//      if(readByte == -3){   //
//        movement = clockwiseset;
//        myservo.write(movement);
//        Serial.print("Servo value = ");
//        Serial.println(myservo.read());
//      }
//      if(readByte == -4){   //
//        movement = haltset;
//        myservo.write(movement);
//        Serial.print("Servo value = ");
//        Serial.println(myservo.read());
//      }
//      if(readByte == -5){
//        movement = counterclockwiseset;
//        myservo.write(movement);
//        Serial.print("Servo value = ");
//        Serial.println(myservo.read());
//      }

    if(readByte >= 0 && readByte <= 7){
          switch (readByte) {
            case topspin:
              Serial.println("topspin");
              computeRotation(curpos, topspin);
              curpos = topspin;
              break;
            case toprightsidespin:
              Serial.println("toprightsidespin");
              computeRotation(curpos, toprightsidespin);
              curpos = toprightsidespin;
              break;
            case rightsidespin:
              Serial.println("rightsidespin");
              computeRotation(curpos, rightsidespin);
              curpos = rightsidespin;
              break;
            case backrightsidespin:
              Serial.println("backrightsidespin");
              computeRotation(curpos, backrightsidespin);
              curpos = backrightsidespin;
              break;
            case backspin:
              Serial.println("backspin");
              computeRotation(curpos, backspin);
              curpos = backspin;
              break;
            case backleftsidespin:
              Serial.println("backleftsidespin");
              computeRotation(curpos, backleftsidespin);
              curpos = backleftsidespin;
              break;
            case leftsidespin:
              Serial.println("leftsidespin");
              computeRotation(curpos, leftsidespin);
              curpos = leftsidespin;
              break;
            case topleftsidespin:
              Serial.println("topleftsidespin");
              computeRotation(curpos, topleftsidespin);
              curpos = topleftsidespin;
              break;
          }
    }
    
    readByte = 0;  
  }
  
//  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
//  myservo.write(104);
//  delay(5000);
//
//  myservo.detach();
//  delay(5000);
// 
//  myservo.attach(9);
//  myservo.write(92);
//  delay(5000);
//
//  myservo.detach();
//  delay(5000);

}


