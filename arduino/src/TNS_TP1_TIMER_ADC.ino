//#include <Arduino.h>
#include "waveheader.h"

#define PinTimer 2
uint16_t value;
#define RC 82
#define BUFFER_SIZE 10
#define OUTPUT_SIZE 24000

//--------Coeff----------
float coeff[BUFFER_SIZE]={
   0.043520086613658394425474540412324131466,
-0.057226900549356370107023650461997021921,
 0.101379636359806471479494405230070697144,
-0.195848367641251241977329300425481051207,
 0.631016794799178937225292429502587765455,
 0.631016794799178937225292429502587765455,
-0.195848367641251241977329300425481051207,
 0.101379636359806471479494405230070697144,
-0.057226900549356370107023650461997021921,
 0.043520086613658394425474540412324131466,
};

void setupTimer(){
  PMC->PMC_PCER0 |= PMC_PCER0_PID27;  // Active le périphérique TC0
  TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_CPCTRG;
  // Définit la source d'horloge à TCLK4 (MCK / 128, 84 MHz / 128 = 656.25 kHz)
  // Active le déclenchement de comparaison RC
  // Définit la valeur RC pour une fréquence samplingFrequency Hz
  TC0->TC_CHANNEL[0].TC_RC = RC;
  // Active l'interruption de comparaison RC
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  // Active l'interruption TC0_IRQn dans le NVIC
  NVIC_EnableIRQ(TC0_IRQn);
}


void setupADC(){
  PMC->PMC_PCER1 |= PMC_PCER1_PID37;     // Active le périphérique ADC
  ADC->ADC_MR = ADC_MR_PRESCAL(3)        // Définit le diviseur de fréquence à 255
                | ADC_MR_STARTUP_SUT64   // Définit le temps de démarrage à 64 périodes d'ADC_CLK
                | ADC_MR_TRACKTIM(15)    // Définit le temps de suivi à 16 périodes d'ADC_CLK
                | ADC_MR_SETTLING_AST3;  // Définit le temps de stabilisation à 17 période d'ADC_CLK
                //| ADC_MR_LOWRES; //Passage en 10 bits de l'ADC
  ADC->ADC_CHER = ADC_CHER_CH7;          // Active le canal 7 (A0)
}

void setupDAC(){
  // Active le périphérique DAC
  PMC->PMC_PCER1 |= PMC_PCER1_PID38;
  // Configure le DAC en mode normal
  DACC->DACC_MR = DACC_MR_TRGEN_DIS // Désactive le déclencheur externe
                  | DACC_MR_USER_SEL_CHANNEL1 // select canal 1 // DACC_MR_USER_SEL_CHANNEL0
                  | DACC_MR_WORD_HALF // Largeur de mot de 16 bits (0 - 4095)
                  | DACC_MR_REFRESH(1) // Temps de rafraîchissement (dans les cycles de l'horloge du périphérique)
                  | DACC_MR_STARTUP_8 // Temps de démarrage (8 * 6 cycles)
                  | DACC_MR_MAXS; // Utilise le contrôleur DMA pour les transferts DAC
  // Active le canal 1 du DAC
  DACC->DACC_CHER = DACC_CHER_CH1;// DACC_CHER_CH0
  DACC->DACC_IER |= DACC_IER_EOC;
  // Active l'interruption DACC_IRQn dans le NVIC 
  NVIC_EnableIRQ(DACC_IRQn);
}

void DACC_Handler() {
  DACC->DACC_ISR;  //  effacer le register d’état “status register”
}

void TC0_Handler() {
  // Lecture du registre INT pour effacer le drapeau d'interruption
  TC0->TC_CHANNEL[0].TC_SR;
  // Lancement manuel de la conversion de l'ADC
  ADC->ADC_CR = ADC_CR_START;
  //Changement de la l'état du pin définit pour afficher la freq du timer à l'oscilloscope
  //digitalWrite(PinTimer, HIGH);
  //digitalWrite(PinTimer, LOW);
}

int16_t filter_taps[BUFFER_SIZE];
uint16_t filteredSignal[OUTPUT_SIZE];

/*void CircularBuffer() {
  int tempoBuffer[BUFFER_SIZE];
  int adcBufferIndex = 0;
  for(int i=0; i < OUTPUT_SIZE; i++) {
    while((ADC->ADC_ISR & 0x80)==0); // attente de la fin de la conversion
    tempoBuffer[adcBufferIndex] = ADC->ADC_CDR[7]; // sauvegarde du signal dans le buffer 

    adcBufferIndex++;   // incrementation de l'index du buffer cirulaire
    uint16_t sumIndex = adcBufferIndex; // update de l'index pour le bon indexage des valeurs en fonction des coeffs 
    if(adcBufferIndex == BUFFER_SIZE) { // modulo pour remettre à 0 
      adcBufferIndex = 0;
    }
    
    // Calcul du filtrage sur les 15 valeurs du buffer 
    uint32_t acc = 0;
    
    for (int l = 0; l < BUFFER_SIZE; l++) { // multiplication des valeurs du buffer par les coeffs

      // gestion de l'index interne au buffer pour le calcul du filtre
      if( sumIndex > 0 ) {
        sumIndex--;
      } else {
        sumIndex=BUFFER_SIZE-1;
      }
      // calcule du filtre sur 32 bit
      acc += coeff[l] * tempoBuffer[sumIndex];
      
    }
    filteredSignal[i] =  acc >> 15; // shift de 15 bit pour repasser sur 16 bit
    Serial.println(filteredSignal[i]);
  }
}*/

void CircularBuffer() {
  int tempoBuffer[BUFFER_SIZE];
  int adcBufferIndex = 0;

  const uint32_t recordedDataSize = 24000;
  uint8_t recordedData[recordedDataSize];
  for(int i=0; i < OUTPUT_SIZE; i++) {
    while((ADC->ADC_ISR & 0x80)==0); // attente de la fin de la conversion
    tempoBuffer[adcBufferIndex] = ADC->ADC_CDR[7]; // sauvegarde du signal dans le buffer 

    adcBufferIndex++;   // incrementation de l'index du buffer cirulaire
    uint16_t sumIndex = adcBufferIndex; // update de l'index pour le bon indexage des valeurs en fonction des coeffs 
    if(adcBufferIndex == BUFFER_SIZE) { // modulo pour remettre à 0 
      adcBufferIndex = 0;
    }
    
    // Calcul du filtrage sur les 15 valeurs du buffer 
    uint32_t acc = 0;
    
    for (int l = 0; l < BUFFER_SIZE; l++) { // multiplication des valeurs du buffer par les coeffs

      // gestion de l'index interne au buffer pour le calcul du filtre
      if( sumIndex > 0 ) {
        sumIndex--;
      } else {
        sumIndex=BUFFER_SIZE-1;
      }
      // calcule du filtre sur 32 bit
      acc += coeff[l] * tempoBuffer[sumIndex];
      
    }
    //Serial.println(acc);
    filteredSignal[i] =  acc; // shift de 15 bit pour repasser sur 16 bit
    Serial.println(filteredSignal[i]);
    recordedData[i] = filteredSignal[i];

  // Read audio data from the ADC
  /*for (uint32_t i = 0; i < recordedDataSize; i++) {
    recordedData[i] = analogRead(adcPin) >> 2; // Adjust the bit shifting to match your ADC resolution
    delayMicroseconds(10); // Adjust the delay as needed for your sampling rate
  }*/
  }
  // Save the recorded audio data to the buffer
  saveAudioData(recordedData, recordedDataSize);

  // Retrieve the WAV data from the buffer
  uint8_t wavData[maxBufferSize + sizeof(wavHeader)];
  uint32_t wavDataSize;
  getWavData(wavData, &wavDataSize);

  // Send the WAV data to Audacity via Serial communication
  Serial.write(wavData, wavDataSize);

  // Reset the buffer position for the next recording
  bufferPosition = 0;
  
}

void setup() {
  //Communication série au maximum de l'Arduino DUE
  Serial.begin(460800); 
  setupADC();
  setupDAC();
  setupTimer();
  pinMode(PinTimer, OUTPUT);
  //Demarrage du Timer 0
  TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
  CircularBuffer();
}
int e = 1;
void loop() {    
  /*if(ADC->ADC_ISR & ADC_ISR_EOC7){ //Code à exécuter
    value = ADC->ADC_CDR[7];
    DACC->DACC_CDR = DACC_CDR_DATA(value);
    while (!(DACC->DACC_ISR & DACC_ISR_TXRDY));
    Serial.println(value);
  }*/
  //if(e==1){
  //CircularBuffer();
  //e=2;
  //}
}
