#include "convolution.h"

float kernel[3][3] = {{-0.3887915, 2.7433753,-0.15814383 },
                      {-0.34392855, 2.868973, -0.17676564},
                      {-0.320773, 2.7739594, -0.3000964}};

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

