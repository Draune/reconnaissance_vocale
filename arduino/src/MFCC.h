#include <arduinoMFCC.h>

#define MFCC_INPUT_SIZE 4
#define MFCC_OUTPUT_SIZE_X 62
#define MFCC_OUTPUT_SIZE_Y 13


void MFCC(uint16_t inputs[MFCC_INPUT_SIZE],float ouputs[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y]);