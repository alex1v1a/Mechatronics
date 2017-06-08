#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int butt = 8;
int butts = 0;
int dist;
// int i = 0;

void setup() {
  Serial.begin(9600);

//  Wire.begin();
//  pinMode(2, OUTPUT);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  
  Wire.begin();
  
  // sensor.init();
  // sensor.configureDefault();
  // sensor.setTimeout(500);
  pinMode(2, OUTPUT);
  pinMode(butt,INPUT);
  
}

void loop() {

  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lcd.setCursor(0, 0);
  lcd.print("Read measurement");

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance(mm):"); 
    Serial.println(measure.RangeMilliMeter);
    lcd.setCursor(0, 1);
    lcd.print(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
    lcd.setCursor(0, 0);
    lcd.print("Out of range");
  }
    
  delay(100);
  lcd.print(millis() / 1000);

  dist = measure.RangeMilliMeter;
 
  butts = digitalRead(butt);
  if(butts == 1){
    while(dist <= 50){
      digitalWrite(2,HIGH);
      dist = measure.RangeMilliMeter;
    }
  } else if(butts == 0){
    digitalWrite(2,LOW);
  }

Test Relay
//    if(i%2 != 1){
//    digitalWrite(2,HIGH);
//  } else{
//    digitalWrite(2,LOW);
//  }
//  i++;
//  delay(1000);


}
