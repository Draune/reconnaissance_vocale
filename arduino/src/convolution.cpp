#include "convolution.h"

float kernel[3][3] = {{-0.5326495, 2.6255102,-0.49177617 },
                      {-0.5265761, 2.643906, -0.44409272},
                      {-0.55045366, 2.625338, -0.47660905}};

void convolution(float inputs[CONV_INPUT_SIZE_X][CONV_INPUT_SIZE_Y], float outputs[CONV_OUTPUT_SIZE_X][CONV_OUTPUT_SIZE_Y]){
    for (int I=0; I<CONV_OUTPUT_SIZE_X; I++){
        for(int J=0;J<CONV_OUTPUT_SIZE_Y;J++){
            outputs[I][J] = .0f;
            for (int i = 0;i<3;i++){
                for (int j = 0;j<3;j++){
                    outputs[I][J] += inputs[I+i][J+j]*kernel[i][j];
                }
            }
        }
    }
}

