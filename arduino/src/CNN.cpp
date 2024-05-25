#include "CNN.h"

float outputs_conv[CONV_OUTPUT_SIZE_X][CONV_OUTPUT_SIZE_Y] = {0.0f};
float outputs_pool[POOL_OUTPUT_SIZE_X][POOL_OUTPUT_SIZE_Y] = {0.0f};
float outputs_flat[FLAT_OUTPUT_SIZE] = {0.0f};

void prediction(float inputs[CNNDATA_INPUT_SIZE_X][CNNDATA_INPUT_SIZE_Y],float outputs[NN_OUTPUT_SIZE])
{
    convolution(inputs,outputs_conv);
    maxpool(outputs_conv,outputs_pool);
    flatten(outputs_pool,outputs_flat);

    nn(outputs_flat,outputs);
}