#include "maxpool.h"

void maxpool(float inputs[POOL_INPUT_SIZE_X][POOL_INPUT_SIZE_Y], float outputs[POOL_OUTPUT_SIZE_X][POOL_OUTPUT_SIZE_Y])
{
    for (int I = 0; I < POOL_OUTPUT_SIZE_X; I++)
    {
        for (int J = 0; J < POOL_OUTPUT_SIZE_Y; J++)
        {
            outputs[I][J] = 0.f;
            for (int i = 0; i < POOL_X; i++)
            {
                for (int j = 0; j < POOL_Y; j++)
                {
                    if (inputs[I * POOL_X + i][J * POOL_Y + j] > outputs[I][J])
                    {
                        outputs[I][J] = inputs[I * POOL_X + i][J * POOL_Y + j];
                    }
                }
            }
        }
    }
}