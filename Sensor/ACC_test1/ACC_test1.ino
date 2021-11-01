//********************************
//加速度センサの値を取得するプログラム
//********************************
void setup()
{
// シリアルモニターの初期化をする
Serial.begin(9600) ;
}
void loop()
{
long x , y , z ;
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

Serial.print("X:");
Serial.print(x_acc);
Serial.print(" Y:");
Serial.print(y_acc);
Serial.print(" Z:");
Serial.print(z_acc);
Serial.println(" [G]");

//Serial.print("X:");
//Serial.print(x_acc * ms2);
//Serial.print(" Y:");
//Serial.print(y_acc * ms2);
//Serial.print(" Z:");
//Serial.print(z_acc * ms2);
//Serial.println("m/s^2");

delay(1000) ;
}
