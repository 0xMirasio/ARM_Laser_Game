
#include "gassp72.h"
#include <stdlib.h>
#include <time.h>
#include  <stdio.h>
#define SYSTICK_PER 360000 // (360000 ticks équivaut à 5ms)
#define M2TIR 984064 
/*
A/2 * 64
= 1982
puis 1982^2
=3936256
format : 16.0 * 1.15 => 17.15 ^ 2 => 34.30
donc 3936256/4 = 984064
*/

extern int dft(short* signal, int k);
extern int TabSig[];

// CONSTANTE -----------------------
short int DMA[64];
int val_k[6] = {17 , 18 ,19 ,20 ,23 ,24};
int compteur[6] = {0,0,0,0,0,0};
int score[6] = {0,0,0,0,0,0};

// --------------------

void sys_callback(void) {
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (int i=0; i<6 ; i++) {
			if (dft(DMA, val_k[i]) > M2TIR) {
					compteur[i]++;
			}
			else {
					compteur[i] = 0;
			}
	}
}
int main(void)
{
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 0x33 );
	Single_Channel_ADC( ADC1, 2 );
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1( 0, (vu16*)DMA );
	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff(SYSTICK_PER);
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;

while	(1)
	{
		for (int i=0 ; i<6 ; i++ ) {
			if (compteur[i] > 4){
					score[i] +=1;
			}
		}
			
	}
}
