#include <Wire.h>
#include <VL6180X.h>

VL6180X sensor;

int butt = 8;
int butts =0;
int dist;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
  pinMode(2, OUTPUT);
  pinMode(butt,INPUT);
  
}

void loop() {
  dist= sensor.readRangeSingle();
 
  butts= digitalRead(butt);
  if(butts ==1){
    while(dist<=50){
      digitalWrite(2,HIGH);
      dist= sensor.readRangeSingle();
    }
  
  }else if(butts ==0){
    digitalWrite(2,LOW);
  }
}
