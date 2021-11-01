//#include <Servo.h>
//
//Servo myservo; //Servoオブジェクトを作成
//
//void setup() {
//  myservo.attach(13); //13番ピンにサーボ制御線（オレンジ）を接続
//}
//
//void loop() {
//  myservo.write(180); //180度へ回転 
//  delay(1000);
//  myservo.write(0); //元に戻る
//  delay(1000);
//}

//#include "esp_system.h"
//
//
//
//void setup() { 
//  Serial.begin(115200);
//  ledcSetup(0, 50, 10);  // 0ch 50 Hz 10bit resolution
//  ledcAttachPin(13, 0); // 13pin, 0ch
//
//int min= 26;  // (26/1024)*20ms ≒ 0.5 ms  (-90°)
//int max = 123; // (123/1024)*20ms ≒ 2.4 ms (+90°)
//int n = min;
//
//}
//
//void loop() {
//  
//int min= 26;  // (26/1024)*20ms ≒ 0.5 ms  (-90°)
//int max = 123; // (123/1024)*20ms ≒ 2.4 ms (+90°)
//int n = min;
//  
//  ledcWrite(0, n);
//  n+=5;
//  if (n > max) 
//  {n = min;
//  };
//  delay(500);
//}



#include <ESP32Servo.h>

Servo servo1; // create four servo objects 
Servo servo2; // create four servo objects 
Servo servo3; // create four servo objects 
Servo servo4; // create four servo objects 
Servo servo5; // create four servo objects 

int servo1Pin = 13;
int servo2Pin = 12;
int servo3Pin = 14;
int servo4Pin = 27;
int servo5Pin = 26;

// Published values for SG90 servos; adjust if needed
int minUs = 500;
int maxUs = 2400;

int pos = 10;      // position in degrees

void setup() {
  servo1.setPeriodHertz(50);      // Standard 50hz servo sg90
  servo2.setPeriodHertz(50);      // Standard 50hz servo sg90
  servo3.setPeriodHertz(50);      // Standard 50hz servo sg90
  servo4.setPeriodHertz(50);      // Standard 50hz servo sg90
  servo5.setPeriodHertz(50);      // Standard 50hz servo sg90
  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);
  servo3.attach(servo1Pin, minUs, maxUs);
  servo4.attach(servo2Pin, minUs, maxUs);
  servo5.attach(servo1Pin, minUs, maxUs);
  }

void loop() {
  for (pos = 10; pos <= 170; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    servo5.write(pos);
    delay(10);             // waits 100ms for the servo to reach the position
  }
  
  for (pos = 170; pos >= 10; pos -= 1) { // sweep from 180 degrees to 0 degrees
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    servo5.write(pos);
    delay(10);
  }
}
