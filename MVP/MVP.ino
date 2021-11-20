#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ESP32Servo.h>


///////////BLE_Unity////////////////
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
int n = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

//#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
//#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"


// 10/29 UNITY taiou
#define SERVICE_UUID        "00002220-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID "00002221-0000-1000-8000-00805F9B34FB"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

////////////赤外線センサー////////////
int ir = 16;
int ir_val = 0;
int k = 0;
////////////////////////////////////


///////////////////マイク関係//////////
int mk = A12;
float mk_val = 0;
float mk_val_1 =0;
float mk_val_2 =0;
float mk_threshold = 2.11;
//////////////////////////////////////


///////////////////スピーカー関係////////////
#define BUZZER_PIN 17
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

///////////SET UP//////////

void setup() {
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("MyESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");

   //pinMode(ir,INPUT); //16ピンに接続した赤外線センサ
  
  pinMode(mk, INPUT);//A10ピンに接続したマイクセンサ
  
  ledcSetup(2,16000,8);
  ledcAttachPin(BUZZER_PIN,2); //スピーカーピン
//  ledcAttachPin(IN1, CHANNEL_0);
//  ledcAttachPin(IN2, CHANNEL_1);
  
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
  //エラー音/////////////
//    ledcWriteTone(2,C10);
//    delay(200);
//    ledcWriteTone(2,C12);
//    delay(600);
//    ledcWriteTone(2,C10);
//    delay(200);
//    ledcWriteTone(2,0.0);


////ゼルダ謎解き音///////
//  ledcWriteTone(2, 3136); // ソ
//  delay(BEAT);
//  ledcWriteTone(2, 2960); // ♯ファ
//  delay(BEAT);
//  ledcWriteTone(2, 2489); // ♯レ
//  delay(BEAT);
//  ledcWriteTone(2, 1760); // ラ
//  delay(BEAT);
//  ledcWriteTone(2, 1661); // ♯ソ
//  delay(BEAT);
//  ledcWriteTone(2, 2637); // ミ
//  delay(BEAT);
//  ledcWriteTone(2, 3322); // ♯ソ
//  delay(BEAT);
//  ledcWriteTone(2, 4186); // ド
//  delay(BEAT);
//  ledcWriteTone(2, 0);    // 音を止める


 ledcWriteTone(2, 1318.510); //ミ
  delay(125);
  ledcWriteTone(2, 1567.982); //ソ
  delay(125);
  ledcWriteTone(2, 2637.020); //ミ
  delay(125);
  ledcWriteTone(2, 2093.005); //ド
  delay(125);
  ledcWriteTone(2, 2349.318); //レ
  delay(125);
  ledcWriteTone(2, 3135.963); //ソ
  delay(125);
  ledcWriteTone(2, 0);

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
  z = analogRead(A7) ; // Ｚ軸

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

///サーボモータ動作(前足)
void Func_Servo_Front(){
  
  for (pos = 10; pos < 90; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);
    servo2.write(pos);
//    servo3.write(pos);
//    servo4.write(pos);
//    servo5.write(pos);
    delay(10);   // waits 100ms for the servo to reach the position
  }
    
  for (pos = 90; pos >= 10; pos -= 1) { // sweep from 180 degrees to 0 degrees
    servo1.write(pos);
    servo2.write(pos);
//    servo3.write(pos);
//    servo4.write(pos);
//    servo5.write(pos);
    delay(10);
  }  
  return;
}

///サーボモータ動作(後足)
void Func_Servo_Back(){
  
  for (pos = 10; pos < 90; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
//    servo1.write(pos);
//    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
//    servo5.write(pos);
    delay(10);   // waits 100ms for the servo to reach the position
  }
    
  for (pos = 90; pos >= 10; pos -= 1) { // sweep from 180 degrees to 0 degrees
//    servo1.write(pos);
//    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
//    servo5.write(pos);
    delay(10);
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
          delay(30);
}

void loop() {
  
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }

  mk_val_1 =0;
  mk_val_2 =0;
  mk_val_1 = mk_read();
  mk_val_2 = mk_read();
  mk_val = abs(mk_val_1 - mk_val_2);
// mk_val = abs(mk_val_1);
  
  if(mk_val >= 0.5) {
    ledcSetup(2,16000,8);
    playmusic();
    Serial.println(mk_val);
    delay(10);

    value = 0x64;

    for(n=0; n<100; n++){
    pCharacteristic->setValue((uint8_t*)&value, 4);
    pCharacteristic->notify();
    }
    
    n=0;

  }  
  
  z_acc = 0; 
  z_acc = Func_Acc_z();
  
  if(z_acc <= 0.75 ){
    Func_Servo_Back();
//    Func_Servo_Stop();
    delay(100);
  };

  
  ir_val = ir_read();
  if(ir_val == 1){
    
    k = k + 1;
    if(k == 1000){
    Func_Servo_Front();
    delay(2000);
    k = 0;
    
    }
  }

    value = 0xFF;
    pCharacteristic->setValue((uint8_t*)&value, 4);
    pCharacteristic->notify();

}
    


   
