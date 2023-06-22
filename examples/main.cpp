#include <Arduino.h>
#include <WeighingScale.h>

WeighingScale myScale(Serial2, 9600);

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600); while (!Serial) {;}
  myScale.begin();
  Serial.println("Mulai");
}
void loop() {
  // put your main code here, to run repeatedly:
  float weight = myScale.getWeight(true);
}