#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include <Arduino.h>

#define CONV_INPUT_SIZE_X 6
#define CONV_INPUT_SIZE_Y 6
#define CONV_OUTPUT_SIZE_X CONV_INPUT_SIZE_X-2
#define CONV_OUTPUT_SIZE_Y CONV_INPUT_SIZE_Y-2

void convolution(float inputs[CONV_INPUT_SIZE_X][CONV_INPUT_SIZE_Y], float outputs[CONV_OUTPUT_SIZE_X][CONV_OUTPUT_SIZE_Y]);

#endif