#include "gassp72.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "etat.h"

#define pwn_periode 360 // KhZ
#define SYSTICK_PER 360000 // (360000 ticks équivaut à 5ms)
#define M2TIR 984064 

type_etat etat;
extern void callback_son(void);
extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;
extern int dft(short* signal, int k);
extern int TabSig[];




// CONSTANTES -----------------------
short int DMA[64];
int val_k[] = {17 , 18 ,19 ,20 ,23 ,24};
int compteur[] = {0,0,0,0,0,0};
int score[] = {0,0,0,0,0,0};


int trame = 0x33; //Scores théoriques : 1, 2, 3, 4, 5, 0


void init_son() {
	
	etat.resolution = PWM_Init_ff( TIM3, 3, pwn_periode );
	etat.son = &Son;
	etat.taille = LongueurSon;
	etat.position = 0;
	etat.periode_ticks = PeriodeSonMicroSec*72;
	
	Timer_1234_Init_ff( TIM4, etat.periode_ticks );
	Active_IT_Debordement_Timer( TIM4, 2, callback_son );
	etat.position = etat.taille; // pour injectez du silence tant qu'un tir n'est pas detecté
	Run_Timer( TIM4 );

}

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
	for (int i=0 ; i<6 ; i++ ) {
			if (compteur[i] == 13){
				score[i] +=1;
				etat.position =0;
			}
		}
}
int main(void)
{
	


	CLOCK_Configure();
	
	Init_TimingADC_ActiveADC_ff( ADC1, trame );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, (vu16*)DMA );
	Systick_Period_ff(SYSTICK_PER);
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;
	
	init_son();


	while	(1) {}
}
