	thumb
	area  moncode, code, readwrite
	export callback_son
	import LongueurSon 
	import PeriodeSonMicroSec
	import Son

TIM3_CCR3	equ	0x4000043C	; adresse registre PWM

E_POS	equ	0
E_TAI	equ	4
E_SON	equ	8
E_RES	equ	12
E_PER	equ	16
		
		
callback_son 	proc
	push {lr}
	ldr r0, =Son
	ldr r2 , =TIM3_CCR3
	str r0, [r2]
	pop {pc}
	endp

	end


