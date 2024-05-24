#include <Arduino.h>
#include "acquisition.h"

struct wavStruct {
  const char chunkID[4] = {'R', 'I', 'F', 'F'};
  uint32_t chunkSize = 36;
  const char format[4] = {'W', 'A', 'V', 'E'};
  const char subchunkID[4] = {'f', 'm', 't', ' '};
  const uint32_t subchunkSize = 16;
  const uint16_t audioFormat = 1;
  uint16_t numChannels = 1;
  uint32_t sampleRate = 8000;
  uint32_t byteRate = 8000;
  uint16_t blockAlign = 1;
  uint16_t bitsPerSample = 16;
  const char subChunk2ID[4] = {'d', 'a', 't', 'a'};
  uint32_t subChunk2Size = 0;
};

wavStruct wavHeader;

uint16_t data[ACQUISITION_SIZE];

void setup() {
    Serial.begin(460800);
    acquisition(data);
    for(int i = 0;i<ACQUISITION_SIZE;i++){
        Serial.print(data[i]);
        Serial.print('\n');}
    //Serial.write((uint8_t*)(&wavHeader),sizeof(wavStruct));
    //Serial.write((uint8_t*)data,ACQUISITION_SIZE*2);
}

void loop() {
}
