#ifndef FLATTEN_H
#define FLATTEN_H
#include <Arduino.h>
#include "maxpool.h"

#define FLAT_INPUT_SIZE_X POOL_OUTPUT_SIZE_X
#define FLAT_INPUT_SIZE_Y POOL_OUTPUT_SIZE_Y
#define FLAT_OUTPUT_SIZE ((POOL_OUTPUT_SIZE_X)*(POOL_OUTPUT_SIZE_Y))

void flatten(float inputs[FLAT_INPUT_SIZE_X][FLAT_INPUT_SIZE_Y], float outputs[FLAT_OUTPUT_SIZE]);

#endif