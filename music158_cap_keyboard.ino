#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */


CapacitiveSensor keys[] = {CapacitiveSensor(2,3), CapacitiveSensor(2,4), 
                           CapacitiveSensor(2,5), CapacitiveSensor(2,6),
                           CapacitiveSensor(2,7), CapacitiveSensor(2,8),
                           CapacitiveSensor(2,9), CapacitiveSensor(2,10),
                           CapacitiveSensor(2,11), CapacitiveSensor(2,12)};
int numKeys;

int threshold = 200;

void setup() {
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   numKeys = sizeof(keys)/sizeof(CapacitiveSensor);
}

void loop() {
  long start = millis();

  for (int i=0; i<numKeys; i++) {
    long total = keys[i].capacitiveSensor(15);
    if (total > threshold) {

      Serial.println(i); 
    }
  }
  
  delay(10);                             // arbitrary delay to limit data to serial port 
}
