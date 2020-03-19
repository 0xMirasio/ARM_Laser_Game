; ce programme est pour l'assembleur RealView (Keil)
	thumb
	area  moncode, code, readonly
	export callback
	export init
;0x20000000 ; la mémoire est dispo

init		proc
	mov r2, r0
	mov r0, #0x20000000
	str r2, [r0]
	bx lr
	endp
		
		
callback	proc
	
GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register
	mov r1, #0x20000000
	ldr r1, [r1]
	ldr	r3, =GPIOB_BSRR
	cmp r1, #0x00020000
	beq m1
	bne m0
main
	str	r1, [r3]
	mov r0, #0x20000000
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


