#include <arduinoMFCC.h>
#include"acquisition.h"

// Paramètres MFCC
#define MFCC_SIZE 13
#define DCT_MFCC_SIZE 13
#define FRAME_SIZE 256
#define SAMPLE_RATE 8000             // Fréquence d'échantillonnage
#define AUDIO_LENGTH ACQUISITION_SIZE // Durée du signal audio en échantillons (t * fréquence d'échantillonage)

#define MFCC_INPUT_SIZE ACQUISITION_SIZE
#define MFCC_OUTPUT_SIZE_X ((ACQUISITION_SIZE-FRAME_SIZE)/(FRAME_SIZE/2))
#define MFCC_OUTPUT_SIZE_Y 13

void init_MFCC();
void MFCC(uint16_t inputs[MFCC_INPUT_SIZE],float outputs[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y]);

// Pour tests de validation :

#define MFCC_PRE_ENPHASIS_INPUT_SIZE MFCC_INPUT_SIZE
#define MFCC_PRE_ENPHASIS_OUTPUT_SIZE FRAME_SIZE

void MFCC_pre_emphasis(uint16_t inputs[MFCC_PRE_ENPHASIS_INPUT_SIZE],float outputs[MFCC_PRE_ENPHASIS_OUTPUT_SIZE]);

#define MFCC_FFT_INPUT_SIZE MFCC_INPUT_SIZE
#define MFCC_FFT_OUTPUT_SIZE FRAME_SIZE

void MFCC_fft(uint16_t inputs[MFCC_FFT_INPUT_SIZE],float outputs[MFCC_FFT_OUTPUT_SIZE]);

void MFCC_mel(uint16_t inputs[MFCC_INPUT_SIZE],float outputs[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y]);
