#include "gassp72.h"
#include <stdlib.h>
#include <time.h>
#include  <stdio.h>
#define SYSTICK_PER 360000 // (360000 ticks équivaut à 5ms)
#define M2TIR 984064 
/*
CALCUL DE M2TIR
A/2 * 64 = 1982
puis 1982^2 =3936256
format : 16.0 * 1.15 => 17.15 ^ 2 => 34.30
Troncature des 32 bits les plus forts => 2 bits de la partie entière supprimés
=> division par 4 donc 3936256/4 = 984064 = M2TIR
*/

extern int dft(short* signal, int k);
extern int TabSig[];

//Définition des variables
//Ce tableau va contenir les valeurs des 64 échantillons du signal recu, d?s qu'on fait une acquisition
short int DMA[64];
//Valeurs de k correspondant aux fréquences des pistolets
int val_k[] = {17 , 18 ,19 ,20 ,23 ,24};
//Tableaux pour compter les occurences d'un signal dans un ?chantillon, et les scores
int compteur[] = {0,0,0,0,0,0};
int score[] = {0,0,0,0,0,0};

////////////////////////////////////////////////////////////////////////
////////////IMPORTANT : paramétrage de la trame de signaux//////////////
////////////////////////////////////////////////////////////////////////

//Décommenter la trame à analyser :

//Avec la valeur 0x33, on observera le signal 1 (1x1, 2x2, 3x3, 4x4, 5x5 et 0x6)
int trame = 0x33; //Scores théoriques : 1, 2, 3, 4, 5, 0
//int trame = 0x52; //Scores théoriques : 1, 2, 3, 4, 5, 15 (0x0000000E)

////////////////////////////////////////////////////////////////////////
////////////IMPORTANT : paramétrage de la trame de signaux//////////////
////////////////////////////////////////////////////////////////////////

//Cette fonction sera régulièrement appelée par le timer pour faire une acquisition de 64 points du signal
//et effectuer une dft dessus pour savoir quel joueur a touché une cible
void sys_callback(void) {
	//On récupère 64 valeurs du signal
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	//On itère sur les 6 valeurs de "fréquences" k des pistolets
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
	//Le deuxième argument de cette fonction nous permet de déterminer quelle trame de signaux
	//va être envoyée.
	
	//Configuration de la trame de signaux
	/*
	
	Digit de      amplitude    amplitude    (en unites ADC)
faible poids     signal 1      bruit
     0 						 31 					 4
     1 						 62 					 4
     2 						 124 					 4
     3 					   248 					 4
     4 						 31 					 12
     5 						 62 					 12
     6 					   124 					 12
     7 						 248 					 12
     8 						 31 					 36
     9 						 62 					 36
     A 						 124 					 36
     B 						 248 					 36
     C 						 31 					 100
     D 						 62 					 100
     E 						 124 					 100
     F 						 248 					 100
		 
	Digit de      amplitude
 fort poids      signal 2
	   3 						 0
	   4 						 248
	   5 						 1000
		 
	*/
	
	Init_TimingADC_ActiveADC_ff( ADC1, trame );
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

	while	(1) {}
}
