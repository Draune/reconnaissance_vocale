#include <Arduino.h>
#include "acquisition.h"
#include "MFCC.h"
#include "CNN.h"

uint16_t data[ACQUISITION_SIZE];
float mfcc_data[MFCC_OUTPUT_SIZE_X][MFCC_OUTPUT_SIZE_Y];
float outputCNN[NN_OUTPUT_SIZE];

void setup()
{
    Serial.begin(9600);
    acquisition(data);
    init_MFCC();
    MFCC(data, mfcc_data);
    Serial.print("\nPredictions : ");
    prediction(mfcc_data,outputCNN);
    int _prediction = 0;
    for (int i = 0; i<NN_OUTPUT_SIZE;i++){
        if(outputCNN[i]>outputCNN[_prediction])
            _prediction = i;
        Serial.print(outputCNN[i]);
        Serial.print(" ");
    }
    if(_prediction == 0)
        Serial.print("\t Bonjour !\n");
    else if(_prediction == 1)
        Serial.print("\t Ca va ?\n");
    else if(_prediction == 2)
        Serial.print("\t Au revoir !");
    else if(_prediction == 3)
        Serial.print("\t Et toi !");
}

void loop()
{
}
