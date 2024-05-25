#include <arduinoMFCC.h>
#include "MFCC.h"

// Déclaration de l'objet MFCC
arduinoMFCC mymfcc(MFCC_SIZE, DCT_MFCC_SIZE, FRAME_SIZE, SAMPLE_RATE);

// stockage les coefficients MFCC
float mfcc[MFCC_SIZE];
float mfcc_inputs[FRAME_SIZE];

void init_MFCC(){
    mymfcc.create_hamming_window();
    mymfcc.create_mel_filter_bank();
    mymfcc.create_dct_matrix();
}

void MFCC(uint16_t inputs[MFCC_INPUT_SIZE], float outputs[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y])
{
    for (int i = 0; i < MFCC_OUTPUT_SIZE_X; i++)
    {
        for (int j = 0; j < FRAME_SIZE; j++)
        {
            mfcc_inputs[j] = float(inputs[i*(FRAME_SIZE/2) + j]);
        }
        // Calcul des MFCCs pour la trame
        mymfcc.computeWithDCT(mfcc_inputs, outputs[i]);
    }
}

void MFCC_pre_emphasis(uint16_t inputs[MFCC_PRE_ENPHASIS_INPUT_SIZE], float outputs[MFCC_PRE_ENPHASIS_OUTPUT_SIZE])
{
    for (int i = 0; i < mymfcc._frame_size; i++)
    {
        mymfcc._frame[i] = float(inputs[i+FRAME_SIZE]);
    }
    mymfcc.pre_emphasis();
    for (int i = 0; i < mymfcc._frame_size; i++)
    {
        outputs[i] = mymfcc._frame[i];
    }
}

void MFCC_fft(uint16_t inputs[MFCC_FFT_INPUT_SIZE], float outputs[MFCC_FFT_OUTPUT_SIZE])
{
    for (int i = 0; i < mymfcc._frame_size; i++)
    {
        mymfcc._frame[i] = float(inputs[i+FRAME_SIZE]);
    }
    mymfcc.pre_emphasis();
    mymfcc.apply_hamming_window();
    mymfcc.apply_fft();
    for (int i = 0; i < mymfcc._frame_size; i++)
    {
        outputs[i] = mymfcc._frame[i];
    }
}

void MFCC_mel(uint16_t inputs[MFCC_FFT_INPUT_SIZE], float outputs[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y])
{
    for (int i = 0; i < MFCC_OUTPUT_SIZE_X; i++)
    {
        for (int j = 0; j < FRAME_SIZE; j++)
        {
            mfcc_inputs[j] = float(inputs[i*(FRAME_SIZE/2) + j]);
        }
        // Calcul des MFCCs pour la trame
        mymfcc.compute(mfcc_inputs, outputs[i]);
    }
}
