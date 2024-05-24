#ifndef __WAVEHEADER_H__
#define __WAVEHEADER_H__
#if defined (ARDUINO_ARCH_SAM)

// Define the WAV header structure
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
  uint16_t bitsPerSample = 8;
  const char subChunk2ID[4] = {'d', 'a', 't', 'a'};
  uint32_t subChunk2Size = 0;
};

// Define the maximum size of the audio buffer
const uint32_t maxBufferSize = 24000; // Adjust this according to your needs

// Create an instance of the WAV header structure
wavStruct wavHeader;

// Create an audio buffer to store the recorded data
uint8_t audioBuffer[maxBufferSize];

// Variable to keep track of the current position in the buffer
uint32_t bufferPosition = 0;
/////////////////////////////////////////////////////////////
// Function to save raw audio data to the buffer
void saveRawAudioData(const uint8_t* data, uint32_t dataSize) {
  // Check if the audio buffer has enough space to store the new data
  if (bufferPosition + dataSize <= maxBufferSize) {
    // Copy the audio data to the buffer
    memcpy(audioBuffer + bufferPosition, data, dataSize);
    
    // Update the buffer position
    bufferPosition += dataSize;
  } else {
    // The audio buffer is full
    // Handle this condition as per your requirements
  }
}
//////////////////////////////////////////////////////////////
// Function to save audio data to the buffer
void saveAudioData(const uint8_t* data, uint32_t dataSize) {
  // Check if the audio buffer has enough space to store the new data
  if (bufferPosition + dataSize <= maxBufferSize) {
    // Copy the audio data to the buffer
    memcpy(audioBuffer + bufferPosition, data, dataSize);
    
    // Update the buffer position and subChunk2Size field in the WAV header
    bufferPosition += dataSize;
    wavHeader.subChunk2Size = bufferPosition;
    
    // Update the chunkSize field in the WAV header
    wavHeader.chunkSize = 36 + wavHeader.subChunk2Size;
    
    // Update the byteRate field in the WAV header
    wavHeader.byteRate = wavHeader.sampleRate * wavHeader.numChannels * (wavHeader.bitsPerSample / 8);
  } else {
    // The audio buffer is full
    // Handle this condition as per your requirements
  }
}

// Function to retrieve the WAV data from the buffer
void getWavData(uint8_t* wavData, uint32_t* dataSize) {
  // Copy the WAV header to the output buffer
  memcpy(wavData, &wavHeader, sizeof(wavHeader));
  
  // Copy the audio data from the buffer to the output buffer
  memcpy(wavData + sizeof(wavHeader), audioBuffer, bufferPosition);
  
  // Set the data size
  *dataSize = sizeof(wavHeader) + bufferPosition;
}
#endif
#endif
