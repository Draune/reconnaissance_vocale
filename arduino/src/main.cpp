#include <Arduino.h>
#include "acquisition.h"
#include "MFCC.h"
#include "CNN.h"

uint16_t data[ACQUISITION_SIZE];
float mfcc_data[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y];

void setup()
{
    Serial.begin(9600);
    acquisition(data);
    init_MFCC();
    MFCC(data, mfcc_data);
    Serial.print("\nPrediction : ");
    float _prediction = prediction(mfcc_data);
    Serial.print(_prediction);
    if(1-_prediction<_prediction)
        Serial.print("\t Bonjour !\n");
    else
        Serial.print("\t Ca va et toi ?\n");
}

void loop()
{
}
