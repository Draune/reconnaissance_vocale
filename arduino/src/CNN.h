#ifndef CNN_H
#define CNN_H

#include"convolution.h"
#include"maxpool.h"
#include"flatten.h"
#include"NN.h"

void prediction(float inputs[CNNDATA_INPUT_SIZE_X][CNNDATA_INPUT_SIZE_Y],float outputs[NN_OUTPUT_SIZE]);

#endif