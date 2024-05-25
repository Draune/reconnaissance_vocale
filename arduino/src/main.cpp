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
    Serial.print("\n[");
    for (int j = 0; j < MFCC_OUTPUT_SIZE_X; j++)
    {
        Serial.print("\n[");
        for (int i = 0; i < MFCC_OUTPUT_SIZE_Y; i++)
        {
            Serial.print(mfcc_data[j][i], 3);
            if(i != MFCC_OUTPUT_SIZE_Y-1)
                Serial.print(", ");
        }
        Serial.print("]");
        if(j != MFCC_OUTPUT_SIZE_X-1)
            Serial.print(",");
    }
    Serial.print("\n]\n");
}

void loop()
{
}
