#include "acquisition.h"
#include "buffer.h"

#define PinTimer 2
uint16_t value;
#define RC 20
int nb_enregistrement;
uint32_t nb_pour_echantillonement;

void setupTimer()
{
    TC0->TC_CHANNEL[0].TC_CCR &= ~TC_CCR_CLKDIS;
    PMC->PMC_PCER0 |= PMC_PCER0_PID27; // Active le périphérique TC0
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

void setupADC()
{
    PMC->PMC_PCER1 |= PMC_PCER1_PID37;    // Active le périphérique ADC
    ADC->ADC_MR = ADC_MR_PRESCAL(5)       // Définit le diviseur de fréquence à 255
                  | ADC_MR_STARTUP_SUT64  // Définit le temps de démarrage à 64 périodes d'ADC_CLK
                  | ADC_MR_TRACKTIM(15)   // Définit le temps de suivi à 16 périodes d'ADC_CLK
                  | ADC_MR_SETTLING_AST3; // Définit le temps de stabilisation à 17 période d'ADC_CLK
                                          //| ADC_MR_LOWRES; //Passage en 10 bits de l'ADC
    ADC->ADC_CHER = ADC_CHER_CH7;         // Active le canal 7 (A0)
}

void setupDAC()
{
    // Active le périphérique DAC
    PMC->PMC_PCER1 |= PMC_PCER1_PID38;
    // Configure le DAC en mode normal
    DACC->DACC_MR = DACC_MR_TRGEN_DIS           // Désactive le déclencheur externe
                    | DACC_MR_USER_SEL_CHANNEL1 // select canal 1 // DACC_MR_USER_SEL_CHANNEL0
                    | DACC_MR_WORD_HALF         // Largeur de mot de 16 bits (0 - 4095)
                    | DACC_MR_REFRESH(1)        // Temps de rafraîchissement (dans les cycles de l'horloge du périphérique)
                    | DACC_MR_STARTUP_8         // Temps de démarrage (8 * 6 cycles)
                    | DACC_MR_MAXS;             // Utilise le contrôleur DMA pour les transferts DAC
    // Active le canal 1 du DAC
    DACC->DACC_CHER = DACC_CHER_CH1; // DACC_CHER_CH0
    DACC->DACC_IER |= DACC_IER_EOC;
    // Active l'interruption DACC_IRQn dans le NVIC
    NVIC_EnableIRQ(DACC_IRQn);
}

void DACC_Handler()
{
    DACC->DACC_ISR; //  effacer le register d’état “status register”
}

void TC0_Handler()
{
    // Lecture du registre INT pour effacer le drapeau d'interruption
    TC0->TC_CHANNEL[0].TC_SR;
    // Lancement manuel de la conversion de l'ADC
    ADC->ADC_CR = ADC_CR_START;
    // Changement de la l'état du pin définit pour afficher la freq du timer à l'oscilloscope
    // digitalWrite(PinTimer, HIGH);
    // digitalWrite(PinTimer, LOW);
}

void start()
{
    nb_enregistrement = 0;
    nb_pour_echantillonement = 0;
    setupADC();
    setupDAC();
    setupTimer();
    // Demarrage du Timer 0
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

void arreterTimer()
{
    TC0->TC_CHANNEL[0].TC_CCR &= ~TC_CCR_CLKEN;
    TC0->TC_CHANNEL[0].TC_CCR &= ~TC_CCR_SWTRG;
    TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKDIS;
}

void acquisition(uint16_t outputs[ACQUISITION_SIZE])
{
    start();
    while (nb_enregistrement < ACQUISITION_SIZE)
    {
        if (ADC->ADC_ISR & ADC_ISR_EOC7)
        { // Code à exécuter
            value = ADC->ADC_CDR[7];
            value = buff_new_val(value);
            if (value != -1)
            {
                if ((nb_pour_echantillonement & 0x3) == 0x0)
                {
                    outputs[nb_enregistrement] = value;
                    nb_enregistrement++;
                }
                nb_pour_echantillonement++;
            }
        }
    }
    arreterTimer();
}
