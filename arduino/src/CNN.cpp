#include "CNN.h"

float outputs_conv[CONV_OUTPUT_SIZE_X][CONV_OUTPUT_SIZE_Y] = {0.0f};
float outputs_pool[POOL_OUTPUT_SIZE_X][POOL_OUTPUT_SIZE_Y] = {0.0f};
float outputs_flat[FLAT_OUTPUT_SIZE] = {0.0f};

float prediction(float inputs[CNNDATA_INPUT_SIZE_X][CNNDATA_INPUT_SIZE_Y])
{
    convolution(inputs,outputs_conv);
    maxpool(outputs_conv,outputs_pool);
    flatten(outputs_pool,outputs_flat);

    return nn(outputs_flat);
}