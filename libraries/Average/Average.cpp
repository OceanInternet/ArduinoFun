#include "Average.h"

Average::Average(int numReadings) {
    this->numReadings = numReadings;

    for (int i = 0; i < numReadings; i++) {
        this->readings[i] = 0;
    }
}

void Average::update(int newReading) {

    this->addReading(newReading);
}

int Average::getAverage() {

    return this->average;
}

void Average::addReading(int reading) {

    this->total -= this->readings[this->currentIndex];
    // read from the sensor:
    this->readings[this->currentIndex] = reading;
    // add the reading to the total:
    this->total += reading;
    // advance to the next position in the array:
    this->currentIndex++;

    // if we're at the end of the array...
    if (this->currentIndex >= this->numReadings) {
        // ...wrap around to the beginning:
        this->currentIndex = 0;
    }

    // calculate the average:
    this->average = this->total / this->numReadings;
}
