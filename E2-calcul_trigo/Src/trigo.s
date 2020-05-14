	thumb
	area  moncode, code, readwrite
	export test_trigo
	import TabCos
	import TabSin

test_trigo	proc
	mov r12, r1 ; on save l'adresse de S dans r12
	ldr r3, =TabCos ;r3 = adresse du tableau de cosinus
	ldrsh r2, [r3,r0, lsl #1] ; r2 = recup du cos
	mul r2,r2 ;r2 =  cos^2 
	ldr r3, =TabSin ; r3 = adresse du tableau de sinus
	ldrsh r1, [r3,r0, lsl #1] ; r1 = recup du sin
	mul r1,r1 ; r1 = sin^2 
	add r1,r2 ; r1 = sin^2 + cos^2
	str r1, [r12]
	bx lr
	endp	
	
	end