#include "gassp72.h"
#include "etat.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define pwn_periode 360 // KhZ
#define SYSTICK_PER 360000 // (360000 ticks équivaut à 5ms)
#define M2TIR 984064 

//On va stocker toutes les informations sur le son dans la variable etat
type_etat etat;
//Fonction définie dans Son.s
extern void callback_son(void);
//On récupère le son, sa période et sa longueur du son dans le fichier de son en asm obtenu via Wav2asm
//Ici, les infos sont donc stockées dans bruitverre.s
extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;
//Fonction dft définie dans le fichier calcul_dft.s
extern int dft(short* signal, int k);

//Définition des variables
//Ce tableau va contenir les valeurs des 64 échantillons du signal recu, dès qu'on fait une acquisition
short int DMA[64];
//On définie un tableau pour donner la correspondance entre chaque signal et sa fréquence
int val_k[] = {17 ,18 ,19 ,20 ,23 ,24};
//Tableaux pour compter les occurences d'un signal dans un échantillon, et les scores
int compteur[] = {0,0,0,0,0,0};
int score[] = {0,0,0,0,0,0};

//On peut paramétrer la trame que l'on souhaite analyser via cette variable
//Avec la valeur 0x33, on observera le signal 1 (1x1, 2x2, 3x3, 4x4, 5x5 et 0x6)
//avec une amplitude de 248 et un bruit de fond d'amplitude de 4
int trame = 0x33; //Scores théoriques : 1, 2, 3, 4, 5, 0

//Fonction qui initialise le timer pour le son, ainsi que la fonction de callback associée
void init_son() {
	etat.resolution = PWM_Init_ff( TIM3, 3, pwn_periode );
	etat.son = &Son;
	etat.taille = LongueurSon;
	etat.position = 0;
	etat.periode_ticks = PeriodeSonMicroSec*72;
	
	Timer_1234_Init_ff( TIM4, etat.periode_ticks );
	Active_IT_Debordement_Timer( TIM4, 2, callback_son );
	etat.position = etat.taille; //Pour injectez du silence par défaut tant qu'un tir n'est pas detecté
	Run_Timer( TIM4 );
}

//Cette fonction sera régulièrement appelée par le timer pour faire une acquisition de 64 points du signal
//et effectuer une dft dessus pour savoir quel joueur a touché une cible
void sys_callback(void) {
	//Lancement de l'acquisition
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	//Analyse de l'acquisition
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
	//On ne configure qu'une seule fois la CLOCK pour tous les timers
	CLOCK_Configure();
	
	//Configuration du timer principal
	Init_TimingADC_ActiveADC_ff( ADC1, trame );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, (vu16*)DMA );
	Systick_Period_ff(SYSTICK_PER);
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;
	
	//Configuration du timer pour le son
	init_son();

	while	(1) {}
}
