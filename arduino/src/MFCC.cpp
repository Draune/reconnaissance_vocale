#include <arduinoMFCC.h>
#include "MFCC.h"
// Paramètres MFCC
#define MFCC_SIZE 13
#define DCT_MFCC_SIZE 6
#define FRAME_SIZE SAMPLE_RATE/48
#define SAMPLE_RATE 8000  // Fréquence d'échantillonnage
#define AUDIO_LENGTH SAMPLE_RATE*1 // Durée du signal audio en échantillons (t * fréquence d'échantillonage)


MFCC ()
// Déclaration de l'objet MFCC
arduinoMFCC mymfcc(MFCC_SIZE, DCT_MFCC_SIZE, FRAME_SIZE, SAMPLE_RATE);

// stockage du signal audio
int16_t audioSignal[AUDIO_LENGTH];

// stockage les coefficients MFCC
float mfcc[MFCC_SIZE];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  //fonction pour charger le signal audio

  // préparation du sgnal a la conversions en MFCCs
  mymfcc.pre_emphasis((uint16_t)FRAME_SIZE, audioSignal);
  mymfcc.create_hamming_window();

  mymfcc.create_mel_filter_bank();
}

void loop() {

  // Découper le signal audio en 13 trames par secondes superposé à hauteur de 50%
  for (int i = 0; i < AUDIO_LENGTH - FRAME_SIZE; i += FRAME_SIZE / 2) {
    // Calcul des MFCCs pour la trame
    mymfcc.compute(audioSignal + i, mfcc);

  while (true);
  }
}
