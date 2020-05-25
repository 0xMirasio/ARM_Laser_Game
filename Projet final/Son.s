	thumb
	area  moncode, code, readwrite
	export callback_son
	import etat

TIM3_CCr3	equ	0x4000043C	; adresse registre PWM

E_POS	equ	0
E_TAI	equ	4
E_SON	equ	8
E_RES	equ	12
E_PER	equ	16
		
		
callback_son 	proc
	
	ldr r2, =etat ;adresse de la structure
	ldr r0, [r2, #E_POS]  ; on charge la taille 
	ldr r1, [r2, #E_TAI] ; on charge la position 
	cmp r0,r1 ; on compare la position et la taille
	bne son_traitement ; si position=taille, le son est deja terminé, sinon on traite le son
	
	ldr r4,=TIM3_CCr3 ; adr de timer3
	mov r5,#0 
	str r5, [r4]; on injecte 0
	b return
	
son_traitement

	; recuperation du son
	ldr	r3, [r2, #E_SON]
	add	r3, r0 ; reperage de la position du son
	add r0, #2 ; son = 16 bits
	str	r0, [r2, #E_POS]
	
	ldrsh r8, [r3] ; on récupere l'echantillon de son
	
	;calibrage 
	add r8, #32768
	
	;résolution
	ldr r0, [r2, #E_RES] ; on charge la resolution
	mul r8,r0
	lsr r8,#16
	
	;on envoie le son
	ldr r4,=TIM3_CCr3 ;adr du timer
	str r8, [r4] ; on envoie l'echantillon traité pour l'afficher dans le logic analyser
	
	b return
	
return bx lr	
	
	endp

	end


