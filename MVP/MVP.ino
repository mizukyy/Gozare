//all///////////////////////////////
#include <ESP32Servo.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

////赤外線センサー動作確認用
int ir = 16;

int ir_val = 0;
////////////////////////////////////

///////////////////マイク関係//////////
int mk = A10;
int mk_val = 0;
int mk_threshold = 2.11;
//////////////////////////////////////


///////////////////スピーカー関係////////////
#define BUZZER_PIN 25
//音を鳴らす時間
#define BEAT 500
//音階名と周波数の対応
#define C4 261.6
#define C#4 277.18
#define D4 293.665
#define D#4 311.127
#define E4 329.63
#define F4 349.228
#define F#4 369.994
#define G4 391.995
#define G#4 415.305
#define A4 440
#define A#4 466.164
#define B4 493.883
#define C5 523.251
#define C10 300.598
#define C11 500.598
#define C12 420.598
////////////////////////////////////////////////


/////サーボモータ関係////////////////////////////
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
//////////////////////////////////////////////////////////

//////////加速度センサー関係///////////
float z_acc = 0; 
//////////////////////////


////////////////////////////////////

void setup() {
  Serial.begin(9800); //モニターに出力するための設定
  //pinMode(ir,INPUT); //16ピンに接続した赤外線センサ
  
  pinMode(mk, INPUT);//A10ピンに接続したマイクセンサ
  
  ledcSetup(1,16000, 8);
  ledcAttachPin(BUZZER_PIN,1); //スピーカーピン

  servo1.setPeriodHertz(50);      // Standard 50hz servo sg90
  servo2.setPeriodHertz(50);
  servo3.setPeriodHertz(50);
  servo4.setPeriodHertz(50);
  servo5.setPeriodHertz(50);      
  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);
  servo3.attach(servo3Pin, minUs, maxUs);
  servo4.attach(servo4Pin, minUs, maxUs);
  servo5.attach(servo5Pin, minUs, maxUs);


  
}


//赤外線センサー読み取り関数
int ir_read() {
  ir_val = 0;
  ir_val = digitalRead(ir);
  //Serial.println(ir_val);
  return ir_val;
}

//マイクセンサー読み取り関数
float mk_read() {
  mk_val = 0;
  mk_val = analogRead(mk);
  //Serial.println(mk_val);
  mk_val = mk_val * 3.30 / 4095;
  return mk_val;
}

//スピーカー出力関数
void playmusic(){
    ledcWriteTone(1,C10);
    delay(200);
    ledcWriteTone(1,C12);
    delay(600);
    ledcWriteTone(1,C10);
    delay(200);
    ledcWriteTone(1,0);
}

////加速度センサー読み取り
float Func_Acc_z(){
   
  long  x , y , z ;
        x = y = z = 0 ;

  float x_vol, y_vol, z_vol;
        x_vol = y_vol = z_vol = 0;

  float x_acc, y_acc, z_acc;
        x_acc = y_acc = z_acc = 0;
        
  float offset_vol = 1650; 
  float ms2 = 9.80665;


// ACC出力取得
  x = analogRead(A0) ; // Ｘ軸
  y = analogRead(A3) ; // Ｙ軸
  z = analogRead(A6) ; // Ｚ軸

// 電圧[mV]に変換
  x_vol = x * 3.30 / 4095 * 1000;  
  y_vol = y * 3.30 / 4095 * 1000;
  z_vol = z * 3.30 / 4095 * 1000;

// 加速度[G]に変換 Vcc = 3.3V で 660 mv/G
  x_acc = (x_vol - offset_vol) / 660;
  y_acc = (y_vol - offset_vol) / 660;
  z_acc = (z_vol - offset_vol) / 660;

  return z_acc;
}

///サーボモータ動作
void Func_Servo(){
//  int pos = 0;
  
  for (pos = 10; pos < 170; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
   // servo4.write(pos);
   // servo5.write(pos);
    delay(100);   // waits 100ms for the servo to reach the position
  }

//   servo1.write(0);
//   delay(10);
//   servo1.write(180);

    
  for (pos = 170; pos >= 10; pos -= 1) { // sweep from 180 degrees to 0 degrees
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    //servo4.write(pos);
    //servo5.write(pos);
    delay(100);
  }  
  return;
}

///サーボモータストップ
void Func_Servo_Stop(){
          digitalWrite(servo1Pin,LOW); 
          digitalWrite(servo2Pin,LOW); 
          digitalWrite(servo3Pin,LOW);
          digitalWrite(servo4Pin,LOW); 
          digitalWrite(servo5Pin,LOW);
          delay(3000);
}


void loop() {


  mk_val = mk_read();
  if(mk_val > mk_threshold) {
    playmusic();
  }

  z_acc = 0; 
  z_acc = Func_Acc_z();
  
  if(z_acc <= 0.2 ){
//    SerialBT.print(" Z:");
//    SerialBT.print(z_acc);
//    SerialBT.println(" [G]");

    Func_Servo();
//    Func_Servo_Stop();

//   servo1.write(0);
//   delay(100);
//   servo1.write(180);

    
  };

  ir_val = ir_read();
  if(ir_val == 1){
    Func_Servo();
  }
  
  

}
