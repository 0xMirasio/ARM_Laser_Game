#include "etat.h"
#include "gassp72.h"
#define pwn_periode 360 // KhZ
//Fonction d�finie dans main.s
extern void callback_son(void);
//On va stocker toutes les informations sur le son dans la variable etat
type_etat etat;
//On r�cup�re le son, sa p�riode et sa longueur du son dans le fichier de son en asm obtenu via Wav2asm
//Ici, les infos sont donc stock�es dans bruitverre.s
extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;

//On va simplement configurer le timer pour qu'il appelle callback_son pour jouer chaque �chantillon su son 
int main(void)
{
	// config port PB0 pour �tre utilis� par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	// config TIM3-CH3 en mode PWM
	etat.resolution = PWM_Init_ff( TIM3, 3, pwn_periode );
	etat.son = &Son;
	etat.taille = LongueurSon;
	etat.position = 0;
	// 72000 tick = 1ms donc X periode us = 72tick*Y tick
	etat.periode_ticks = PeriodeSonMicroSec*72;
	
	// activation de la PLL qui multiplie la fr�quence du quartz par 9
	CLOCK_Configure();
	//config port PB1 pour �tre utilis� en sortie
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la dur�e entre interruptions,
	// exprim�e en p�riodes Tck de l'horloge principale du STM32 (72 MHz)
	Timer_1234_Init_ff( TIM4, etat.periode_ticks );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorit�, timer_callback est l'adresse de cette fonction, a cr��r en asm,
	// cette fonction doit �tre conforme � l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, callback_son );
	// lancement du timer
	Run_Timer( TIM4 );

while	(1) {}
}
