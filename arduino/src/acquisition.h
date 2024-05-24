#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <Arduino.h>

#define ACQUISITION_SIZE 16000

void acquisition(uint16_t outputs[ACQUISITION_SIZE]);

#endif