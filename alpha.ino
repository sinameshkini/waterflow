#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_PCD8544.h>
#define btnNone   0
#define btnUp     1
#define btnRight  2
#define btnDown   3
#define btnLeft   4
#define btnSelect 5
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int number[11]={0,9,1,1,3,8,0,6,0,2,8};
int count = 3;

int readbtn(){
    int adc_key_in = analogRead(1);
    if (adc_key_in > 900) return 0;
    else if (adc_key_in > 650) return 5;
    else if (adc_key_in > 450) return 4; 
    else if (adc_key_in > 280) return 3;
    else if (adc_key_in > 90) return 1;
    else if (adc_key_in < 50) return 2;
}

float distance1(){  
    float duration=0,distance=0,avg=0; 
    for(int i=0;i<count;i++){
        digitalWrite(11, LOW);
        delayMicroseconds(2);
        digitalWrite(11, HIGH);     
        delayMicroseconds(30);              
        digitalWrite(11, LOW);  
        duration = pulseIn(10, HIGH);
        distance = ((duration / 2) * 0.0345);
        avg+=distance;
        delay(300);
    }
    avg/=count;
    return avg;   
}

float distance2(){  
    float duration=0,distance=0,avg=0; 
    for(int i=0;i<count;i++){
        digitalWrite(9, LOW);
        delayMicroseconds(2);
        digitalWrite(9, HIGH);     
        delayMicroseconds(30);              
        digitalWrite(9, LOW);  
        duration = pulseIn(8, HIGH);
        distance = ((duration / 2) * 0.0345);
        avg+=distance;
        delay(300);
    }
    avg/=count;
    return avg;   
}

void setup() {
      Serial.begin(9600);
      pinMode(10,INPUT);//echo of sensor 1
      pinMode(11,OUTPUT);//triger 1
      pinMode(8,INPUT);//echo of sensor 2//green
      pinMode(9,OUTPUT);//triger 2//white
      display.begin();
      display.setContrast(60);
      display.clearDisplay();
      display.setCursor(20,10);
      display.print("Welcome");
      display.setCursor(10,30);
      display.print("Starting...");
      display.display();
}

void loop() {
      while(readbtn() != btnSelect){
          display.clearDisplay();
          display.setCursor(0,0);
          display.print("dist1: ");
          display.setCursor(40,0);
          display.print(distance1());
          display.setCursor(0,10);
          display.print("dist2: ");
          display.setCursor(40,10);
          display.print(distance2());
          display.setCursor(30,30);
          display.print("MENU");
          display.display();
      }
      display.clearDisplay();
      display.display();
      while(readbtn() == btnSelect){};
      bool menu=0;
      while(readbtn() != btnSelect){
          display.clearDisplay();
          if(menu==0)display.print("*");
          display.setCursor(5,0);
          display.print("Change Number");
          display.setCursor(0,10);
          if(menu==1)display.print("*");
          display.setCursor(5,10);
          display.print("Send MSG\n");
          display.print(readbtn());
          display.display();
          while(readbtn()==btnNone){}
          if(readbtn()==btnDown)menu = !menu; while(readbtn() != btnNone){};
      }
      while(readbtn() != btnNone){};
}

void send_msg(){
      display.clearDisplay();
      display.print("Sending msg...");
      display.display();
      Serial.print("AT");
      delay(500);
      Serial.write(0xD);
      delay(500);
      Serial.print("AT+CMGF=1");
      delay(500);
      Serial.write(0xD);
      delay(900);
      Serial.print("AT+CMGS=");
      delay(800);
      Serial.write(0x22);
      //for(int co=30;co<41;co++){
      //      number[co-30]=EEPROM.read(co);
      //}
      for(int i=0;i<11;i++){
            Serial.print(number[i]);
      }
      delay(500);
      Serial.write(0x22);
      delay(200);
      Serial.write(0xD);
      delay(800);
      Serial.print(" | ");
      delay(300);
      //Serial.print(distance1,distance2);
      delay(300);
      Serial.print(" | ");
      delay(300);
      Serial.write(0x1A);
      delay(800);
      display.clearDisplay();
      display.print("msg sent!");
      delay(2000);
}

