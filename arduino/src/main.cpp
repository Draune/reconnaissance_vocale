#include <Arduino.h>
#include "CNN.h"
#include "test.h"

void setup() {
    Serial.begin(9600);
    float MSE =0.0f;
    Serial.print("\n");
    for (int i = 0 ; i<10;i++){
        Serial.print("Result ");
        Serial.print(i);
        Serial.print(" : ");
        float predic = prediction(testData[i]);
        Serial.println(predic);
        MSE += (predic-testDataResults[i])*(predic-testDataResults[i]);
    }
    Serial.print("MSE: ");
    Serial.print(MSE,7);
}

void loop() {
}
