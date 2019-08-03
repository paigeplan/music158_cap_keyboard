#include <CapacitiveSensor.h>

// MUST BE SET EACH TIME
#define PHOTO_CELL_MAX 955
#define PHOTO_CELL_MIN 510

// number of capactive keys
#define NUM_KEYS 10

// threshold to determine if tapped or not
#define THRESHOLD 10

// use for photocell
#define SENSOR_PIN A0

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

// arbitrary characters to represent keys on the cap board
char keyCode[] = {'{', '|', '}', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// used to disable long press
int canBePressed[10];

void setup() {
   Serial.begin(9600);
   pinMode(SENSOR_PIN, INPUT);
   
   for (int i=0; i<NUM_KEYS; i++) {
      canBePressed[i] = 1;
   }
}

void loop() {
  // TODO: get photocell working
  printCapKeyValue();
  //printPhotoCellValue();
}

void printPhotoCellValue() {
  int reading = analogRead(SENSOR_PIN);
  int scaled = scalePhotoCellReading(reading, PHOTO_CELL_MIN, PHOTO_CELL_MAX, 10, 110);
  Serial.print(char(scaled));
}

void printCapKeyValue() {
    for (int i=0; i<NUM_KEYS; i++) {
    long total = keys[i].capacitiveSensor(1);
    if (total > THRESHOLD) { 
      if (canBePressed[i] != 0) {
        Serial.print(char(i));
        canBePressed[i] = 0;
      }
    }
    else {
      canBePressed[i] = 1;
    }
    delay(10);
  }
}

//  scales x from [sensorLow, sensorHigh] to [newLow, newHigh]
int scalePhotoCellReading(int x, int sensorHigh, int sensorLow, int newHigh, int newLow) {
  //         (b-a)(x - min)
  // f(x) = --------------  + a
  //          max - min
  return ((newHigh-newLow)*(x-sensorLow)/(sensorHigh-sensorLow)) + newLow;
}



