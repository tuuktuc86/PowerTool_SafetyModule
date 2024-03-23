#include <Adafruit_NeoPixel.h>
#include "Wire.h"
#include <MPU6050_light.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define NUMPIXELS 3 // Popular NeoPixel ring size
#define PIN        9 // On Trinket or Gemma, suggest changing this to 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
MPU6050 mpu(Wire);

#define ledPin 8
#define button 7
#define TRIG 5 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 4 //ECHO 핀 설정 (초음파 받는 핀)
#define buzzer 3


unsigned long timer = 0;
int state = 0;
int cnt1 = 0;
int cnt2 = 0;
int time1 = 999999;
int alarmState = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(100);

  mpu.setGyroOffsets( 0.0, 0.0, 0.0);
  Serial.println("Done!\n");
  pinMode(buzzer, OUTPUT); //버저용 디지털IO를 출력으로 설정
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pixels.clear(); // Set all pixel colors to 'off'
  showPixel(0);
}

void loop() {
  
  mpu.update();

  long time4 = millis();
  long angleX = mpu.getAngleX();
  long angleY = mpu.getAngleY();
  Serial.print("각도 측정하는데 걸리는 시간 = ");
  Serial.println(millis() - time4);
  Serial.print("angle x = ");
  Serial.println(angleX);
  Serial.print("angle y = ");
  Serial.println(angleY);
  long distance = getDistance();

  getAlarm(alarmState);
  //Serial.print("millis ");
  //Serial.println(millis());
  //Serial.print("alarmstate =  ");
  //Serial.println(alarmState);
  if(millis() - time1 >2000 && alarmState==1){
    alarmState = 0;
  }
  
  cntCal(angleX, distance);
  
  
  alarmDeci();
  relayDeci(digitalRead(button), state);

  mpu.setGyroOffsets( 0.0, 0.0, 0.0);
  mpu.update();
//  Serial.println(angleX);
//  Serial.println(angleY);
  delay(1000);

}



long getDistance() {
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
//  long time3 = millis();
  duration = pulseIn (ECHO, HIGH, 8000 ); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.

  distance = duration * 17 / 1000;
  if(duration == 0){//if duration over 8 milli second, distance is 9999
    distance = 9999;
  }
//  Serial.print("걸리는 시간 : ");
//  Serial.println(millis() - time3);
  Serial.print("DIstance : ");
  Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");
  delay(10);
  return distance;
}

void alarm1() {
  for (int i = 0; i < 50; i++) //출력 주파수
  {

    digitalWrite(buzzer, HIGH); //SOUND ON
    delayMicroseconds(250);
    digitalWrite(buzzer, LOW); //SOUND OFF
    delayMicroseconds(250);

  }
//  Serial.println("1번 알림 on");
  return;
}

void alarm2() {
  for (int i = 0; i < 50; i++) //출력 주파수
  {
    digitalWrite(buzzer, HIGH); //SOUND ON
    delayMicroseconds(200);
    digitalWrite(buzzer, LOW); //SOUND OFF
    delayMicroseconds(200);
  }
//  Serial.println("2번 알림");
  return;
}

void getAlarm(int alarm){
  if(alarm == 0){
    Serial.println("no alarm");
    showPixel(0);
  }
  else if(alarm == 1){
    alarm1();
    showPixel(1);
//    Serial.println("alarm1 on");
  }
  else if(alarm == 2){
    alarm2();
    showPixel(2);
//    Serial.println("alarm2 on");
  }
}

void showPixel(int num){
  if(num==1){
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.show();
  }
  else if(num==2){
    pixels.clear();
     pixels.setPixelColor(2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
  }
  else if(num == 0){
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
  }
}

void cntCal(long angle, long dis){
//  Serial.println(state);
  if (angle < -360 || angle > 360 || dis < 20) {
    cnt2++;
    cnt1++;
    
//    Serial.print("2차 위험 cnt2 = ");
//    Serial.println(cnt2);
//    Serial.print("2차 위험 cnt1 = ");
//    Serial.println(cnt1);
  }
  
  else if (dis < 30 && state != 1) {
    cnt1++;
//    Serial.print("1차 위험cnt2 = ");
//    Serial.println(cnt2);
//    Serial.print("1차 위험cnt1 = ");
//    Serial.println(cnt1);
  }

  else {
    cnt1--;
    cnt2--;
    if (cnt1 <= 0) {
      cnt1 = 0;
      
    }
    if (cnt2 <= 0) {
      cnt2 = 0;
     
      
    }
    
    if(cnt1>=3){
      cnt2 = 3;
      //여기 추가 문제있음 빼
      cnt1 = 3;
    }
    if(cnt2 >=3){
      cnt1 = 3;
      //여기 추가 문제있음 빼
      cnt1 = 3;
    }
//    Serial.print("cnt2 = ");
//    Serial.println(cnt2);
//    Serial.print("cnt1 = ");
//    Serial.println(cnt1);
  }
  return;
}

void relayDeci(int buttonState, int typeState){
  if (buttonState == 1 && typeState == 1) {
      digitalWrite(ledPin, 0);
      showPixel(0);
      Serial.println("초기화");
      state = 0;
      alarmState = 0;
      cnt1 = 0;
      cnt2 = 0;
      time1 = 999999;
    }
}

void alarmDeci(){
  Serial.println("***********************");
  Serial.print("cnt2 = ");
    Serial.println(cnt2);
    Serial.print("cnt1 = ");
    Serial.println(cnt1);
     Serial.print("state = ");
    Serial.println(state);
    Serial.println("***********************");
  if (cnt2 >= 3 ) {
    showPixel(2);
    digitalWrite(ledPin, 1);
    alarmState = 2;
    state = 1;

    cnt2 = 3;
    
//    Serial.println("2차 경고 state = 1, cnt2 = 3");
  }
  
  else if (cnt1 >= 3 && state != 1) {
   showPixel(1);
    alarmState = 1;

    time1 = millis();
    Serial.print("time1 = ");
    Serial.println(time1);


    cnt1 = 3;
//    Serial.println("1차 경고 cnt1 = 3");
  }
}
