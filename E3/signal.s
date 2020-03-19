; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readwrite
	export callback
	export init
	export test_trigo
	import TabCos
	import TabSin

		
etat DCW 2 

;0x20000000 ; la mémoire est dispo

init		proc
	mov r2, r0
	ldr r0, =etat
	str r2, [r0]
	bx lr
	endp


test_trigo	proc
	push {r1}
	ldr r3, =TabCos
	mov r1, #2
	mul r0, r1
	ldrh r2, [r3,r0] ; recup du cos
	mul r2,r2 ; cos^2 
	push {r2} ; on save le cos^2 
	ldr r3, =TabSin ; 
	mov r1, #2
	mul r0, r1
	ldrh r2, [r3,r0] ; on recup le sin
	mul r2,r2 ; sin^2 
	pop {r0}
	add r0,r2 ; sin^2 + cos^2
	pop {r1}
	str r0, [r1]
	bx lr
	endp
	

callback	proc
	
GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register
	ldr r1, =etat
	ldr r1, [r1]
	ldr	r3, =GPIOB_BSRR
	cmp r1, #0x00020000
	beq m1
	bne m0
main
	str	r1, [r3]
	ldr r0, =etat
	str r1, [r0]
	bx lr
	endp

m1
	mov	r1, #0x00000002; passe a 1
	b main
m0
	mov	r1, #0x00020000 ; passe a 0
	b main		

	end


