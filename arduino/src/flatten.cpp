#include "flatten.h"

void flatten(float inputs[FLAT_INPUT_SIZE_X][FLAT_INPUT_SIZE_Y], float outputs[FLAT_OUTPUT_SIZE])
{
    for (int i = 0; i < FLAT_INPUT_SIZE_X; i++)
    {
        for (int j = 0; j < FLAT_INPUT_SIZE_Y; j++)
        {
            outputs[i * FLAT_INPUT_SIZE_Y + j] = inputs[i][j];
        }
    }
}