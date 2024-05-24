#ifndef MAXPOOL_H
#define MAXPOOL_H
#include <Arduino.h>
#include "convolution.h"

#define POOL_INPUT_SIZE_X CONV_OUTPUT_SIZE_X
#define POOL_INPUT_SIZE_Y CONV_OUTPUT_SIZE_Y
#define POOL_OUTPUT_SIZE_X (POOL_INPUT_SIZE_X)/2
#define POOL_OUTPUT_SIZE_Y (POOL_INPUT_SIZE_Y)/2
// taille du maxpool pour chacune des 2 dimensions
#define POOL_X 2
#define POOL_Y 2

void maxpool(float inputs[POOL_INPUT_SIZE_X][POOL_INPUT_SIZE_Y], float outputs[POOL_OUTPUT_SIZE_X][POOL_OUTPUT_SIZE_Y]);

#endif