float duration1, distance1,duration2, distance2;
void distance();

void setup() {
  
Serial.begin(9600);
pinMode(10,INPUT);//echo of sensor 1
pinMode(11,OUTPUT);//triger 1
pinMode(8,INPUT);//echo of sensor 2//green
pinMode(9,OUTPUT);//triger 2//white
pinMode(7,OUTPUT);
}
void loop() {
  digitalWrite(11, LOW);
  delayMicroseconds(2);
  digitalWrite(11, HIGH);
  delayMicroseconds(30);              
  digitalWrite(11, LOW); 
  duration1 = pulseIn(10, HIGH);
  distance1 = ((duration1 / 2) * 0.0345);
  Serial.println(distance1);
  Serial.println(analogRead(0)/5);
  if(distance1 < (analogRead(0)/5)){
    digitalWrite(7,HIGH);
  }else{
    digitalWrite(7,LOW);
  }
  delay(100);
}


 
 
 
