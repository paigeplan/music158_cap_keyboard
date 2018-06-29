#include <Keyboard.h>

#include <CapacitiveSensor.h>


/*
 * Based off the CapitiveSense Library Demo Sketch by Paul Badger 2008
 * 
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */

CapacitiveSensor keys[] = {CapacitiveSensor(2,3), CapacitiveSensor(2,4), CapacitiveSensor(2,5),
                          CapacitiveSensor(2,6), CapacitiveSensor(2,7), CapacitiveSensor(2,8),
                          CapacitiveSensor(2,9), CapacitiveSensor(2,10), CapacitiveSensor(2,11), CapacitiveSensor(2,12)};

// used to disable long press
int canBePressed[10];

// num capactive keys
int numKeys;

// threshold to determine if tapped or not
int threshold = 10;

// TODO: use for photocell
int sensorPin = A0;

void setup() {
   Serial.begin(9600);
   pinMode(sensorPin, INPUT);
   numKeys = sizeof(keys)/sizeof(CapacitiveSensor);
   
   for (int i=0; i<numKeys; i++) {
      canBePressed[i] = 1;
   }
}

void loop() {
  // TODO: get photocell working
  //Serial.println(-analogRead(sensorPin));
  
  for (int i=0; i<numKeys; i++) {
    long total = keys[i].capacitiveSensor(1);
//    Serial.println(total); 
    if (total > threshold) { 
      if (canBePressed[i] != 0) {
        // convert index to ascii value for number since
        // thats what max understands
        int ascii = i + 48;
        Serial.print(i); 
//        Serial.print(": "); 
//        Serial.print(total);
//        Serial.print("    ");
        canBePressed[i] = 0;
      }
    }
    else {
      canBePressed[i] = 1;
    }
    delay(5);
  }
}




