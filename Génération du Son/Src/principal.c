#include "etat.h"
#include "gassp72.h"
#define pwn_periode 360000 // 5ms
extern void callback_son(void);
extern short Son;
extern int LongueurSon;
extern int PeriodeSonMicroSec;

int main(void)
{
	
	type_etat etat;
	// config port PB0 pour être utilisé par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	// config TIM3-CH3 en mode PWM
	etat.resolution = PWM_Init_ff( TIM3, 3, pwn_periode );
	etat.son = &Son;
	etat.taille = LongueurSon;
	etat.position = 0;
	// 72000 tick = 1ms donc X periode us = 72tick*Y tick
	etat.periode_ticks = PeriodeSonMicroSec*72;
	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	//config port PB1 pour être utilisé en sortie
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la durée entre interruptions,
	// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
	Timer_1234_Init_ff( TIM4, etat.periode_ticks );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
	// cette fonction doit être conforme à l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, callback_son );
	// lancement du timer
	Run_Timer( TIM4 );

while	(1)
	{
	}
}
