#include "convolution.h"

float kernel[3][3] = {{-0.66909146, 2.389413,-0.7713469 },
                      {-0.74124795, 2.3633256, -0.879144},
                      {-0.77164555, 2.2567976, -0.81613827}};

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

