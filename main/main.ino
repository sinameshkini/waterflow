#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
const int btnRIGHT = 2;
const int btnUP= 1;
const int btnDOWN = 3;
const int btnLEFT=  4;
const int btnSELECT =5;
const int btnNONE  = 0;
float duration1, distance1,duration2, distance2;
String menuUs = "";
char text;
 int number[11]={0,0,0,0,0,0,0,0,0,0,0};
  int gh,vs,lastButtonPushed = 0 ,d1,d2;
const int sentenceSize = 80;
char sentence[sentenceSize];
char buffer1[40];
char menu1[16]="   send msg  >>";
char menu2[16]="  change num >>";
bool sms_on,auto_flag;
int status_flag;
int adc_key_in  = 0; 
void distance();
void show();
void readBuutton ();
void send_msg();
void change_number();
void calib();
void sms();
void gprs();

void menu(){
 cal: display.clearDisplay();
  display.setCursor(20,20);
  display.print("Calibrate");
  display.display();
  lastButtonPushed=0;
while(lastButtonPushed==0){ readBuutton ();}
switch(lastButtonPushed){
   case btnSELECT:{calib();}
   case btnRIGHT:{sms(); }  
   case btnLEFT:{show();}
}}
void gprs(){
          gprs: display.clearDisplay();
                display.setCursor(20,20);
                display.print("GPRS");
                display.display();
                  lastButtonPushed=0;
                  while(lastButtonPushed==0){ readBuutton ();}
                switch(lastButtonPushed){
                 case btnSELECT:{
                      display.clearDisplay();
                      display.setCursor(20,20);
                      display.print("test");
                      display.display();
                        lastButtonPushed=0;
                        while(lastButtonPushed==0){ readBuutton ();}
                      switch(lastButtonPushed){
                         case btnSELECT:

                         
                         case btnRIGHT:
                            display.clearDisplay();
                            display.setCursor(20,20);
                            display.print("Change url");
                            display.display();
                                lastButtonPushed=0;
                                while(lastButtonPushed==0){ readBuutton ();}
                            switch(lastButtonPushed){
                               case btnSELECT:{
                               }
                               case btnLEFT:{goto gprs;}}
                         case btnLEFT:{break; }}}//cal;
                 case btnRIGHT:{break;}     // cal;   
                 case btnLEFT:{ break;}}//show
  }


void sms(){
  
        display.clearDisplay();
        display.setCursor(20,20);
        display.print("SMS");
        display.display();
        lastButtonPushed=0;
        while(lastButtonPushed==0){ readBuutton ();}
        switch(lastButtonPushed)
          case btnSELECT:
            smstest: display.clearDisplay();
             display.setCursor(20,20);
             display.print("Test");
             display.display();
               lastButtonPushed=0;
               while(lastButtonPushed==0){ readBuutton ();}
             switch(lastButtonPushed){
                case btnSELECT:{send_msg();}
                case btnRIGHT:{
                       display.clearDisplay();
                       display.setCursor(20,20);
                       display.print("Change Number");
                       display.display();
                         lastButtonPushed=0;
                        while(lastButtonPushed==0){ readBuutton ();}
                       switch(lastButtonPushed){
                              case btnSELECT:
                                change_number();
                              case btnRIGHT:{
                                   display.clearDisplay();
                                   display.setCursor(20,20);
                                   display.print("on/off");
                                   display.display();
                                   lastButtonPushed=0;
                                   while(lastButtonPushed==0){ readBuutton ();}
                                   switch(lastButtonPushed){
                                          case btnSELECT:
                                            {sms_on=1;}
                                   }}}}}
  
  
  }
void calib(){
display.clearDisplay();
      display.setCursor(20,20);
      display.print("Sensor1");
      display.display();
      lastButtonPushed=0;
      while(lastButtonPushed==0){ readBuutton ();}
      switch(lastButtonPushed){
            case btnSELECT:{
               d1= EEPROM.read(1);
               display.setCursor(2,10);
               display.print ("d1 = ");
               display.setCursor(10,10);
               display.print (d1);
               display.display();
                lastButtonPushed=0;
                while(lastButtonPushed==0){ readBuutton ();}
                if(lastButtonPushed==btnDOWN){d1=d1-0.01;}
               if(lastButtonPushed==btnUP){d1=d1+0.01;}
               EEPROM.update(1,d1);}
            case btnRIGHT:{     
              display.clearDisplay();
              display.setCursor(20,20);
              display.print("Sensor2");
              display.display();
              lastButtonPushed=0;
               while(lastButtonPushed==0){ readBuutton ();}
              switch(lastButtonPushed){
                 case btnSELECT:{
                     while(lastButtonPushed!=btnSELECT){
                        d1= EEPROM.read(2);
                        display.setCursor(2,10);
                        display.print ("d2 = ");
                        display.setCursor(10,10);
                        display.print (d2);
                        display.display();
                        lastButtonPushed=0;
                        while(lastButtonPushed==0){ readBuutton ();}
                        if(lastButtonPushed==btnDOWN){d2=d1-0.01;}
                        if(lastButtonPushed==btnUP){d2=d1+0.01;}
                        EEPROM.update(2,d2);
                                                      }}}}}
}

void setup() {
  
display.begin();
display.setContrast(50);
display.clearDisplay();

Serial.begin(9600);
pinMode(10,INPUT);//echo of sensor 1
pinMode(11,OUTPUT);//triger 1
pinMode(8,INPUT);//echo of sensor 2//green
pinMode(9,OUTPUT);//triger 2//white
display.setCursor(20,20);
display.print("WELCOME");
display.display();
delay(7000);
Serial.print("AT");//ok or no ready
    delay(100);
    Serial.write(0xD);
Serial.print("AE0");//echo off
    delay(100);
    Serial.write(0xD);
Serial.print("AT+CSTT='CMNET'");//stsrt and set APN(AT+CSTT=\"APN\",\user",\"pass""
    delay(100);
    Serial.write(0xD);
//Serial.print("AT+CGATT=1");
Serial.print("AT+CIICR");
    delay(100);
    Serial.write(0xD);
Serial.print("AT+CIPSTART='TCP','182.168.1.1','8585'");
    delay(100);
Serial.write(0xD);

}
void loop() {
      distance();
      show();
      readBuutton (); 
      if(lastButtonPushed==5)
      {menu();}
//Serial.print("AT+CIPSEND");
//    delay(100);
//    Serial.write(0xD);
//Serial.print(distance1);
//   delay(100);
//    Serial.write(0x1A);
}


void distance(){
digitalWrite(11, LOW);
 digitalWrite(9, LOW);
 delayMicroseconds(2);
 digitalWrite(11, HIGH);
 digitalWrite(9, HIGH);     
 delayMicroseconds(30);              
 digitalWrite(11, LOW); 
 digitalWrite(9, LOW); 
  duration1 = pulseIn(10, HIGH);
  distance1 = ((duration1 / 2) * 0.0345)+d1;
   duration2 = pulseIn(8, HIGH);
  distance2 = ((duration2 / 2) * 0.0345)+d2;
}

void show(){
       display.clearDisplay();
     display.println ("DIST1:");
         display.display();
     display.setCursor(35,0);
     display.println(distance1);
          display.display();
     display.setCursor(0,10);
     display.println ("DIST2:");
          display.display();
     display.setCursor(35,10);
     display.println(distance2);
           display.display();
  }
 void readBuutton ()
  {
adc_key_in = analogRead(1);
if (adc_key_in < 600)
    {
    lastButtonPushed = btnSELECT;
    }
  else if (adc_key_in < 195)
    {
    lastButtonPushed =btnUP; //buttonPinEsc
    }
  else if (adc_key_in < 50) 
    {
    lastButtonPushed = btnRIGHT;
    }
  else if (adc_key_in < 455)
    {
    lastButtonPushed = btnLEFT;
    }
  else if (adc_key_in > 700){
    lastButtonPushed = 0;
    }
    else if (adc_key_in < 350){
    lastButtonPushed = btnDOWN;
    }
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
    for(int co=30;co<41;co++){
        number[co-30]=EEPROM.read(co);
        }
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
    Serial.print(distance1,distance2);
    delay(300);
    Serial.print(" | ");
    delay(300);
    Serial.write(0x1A);
    delay(800);
    display.clearDisplay();
   display.print("msg sent!");
    delay(2000);
}
 void change_number(){
display.clearDisplay();
 display.print(" change num: ");
  display.display();
  display.setCursor(1,1);
  int loc = 2;
  delay(2000);
    while(lastButtonPushed != btnSELECT){
      display.setCursor(0,1);
      for(int co=30;co<41;co++){
        number[co-30]=EEPROM.read(co);
        }
      for(int i=0;i<11;i++){
       display.print(number[i]);
        display.display();
      }
      display.setCursor(loc,1);
      //display.blink();
      while(lastButtonPushed == btnNONE){}  
        if(lastButtonPushed == btnRIGHT){
          if (loc <10) loc++;
        }
        if(lastButtonPushed == btnLEFT){
          if (loc >0) loc--;
        }
        if(lastButtonPushed == btnUP){
          if (number[loc] < 9 ) number[loc]++;
          }
        if(lastButtonPushed == btnDOWN){
          if (number[loc] > 0 ) number[loc]--;
          }
        if(lastButtonPushed == btnSELECT){
          break;
          }
        while(lastButtonPushed != btnNONE){}
        for(int co=30;co<41;co++){
        EEPROM.update(co,number[co-30]);
        }
      }
      while (lastButtonPushed == btnSELECT){}
      for(int co=30;co<41;co++){
        EEPROM.update(co,number[co-30]);
        }
}
 
 
 
 
 

