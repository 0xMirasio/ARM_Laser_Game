
	thumb
	area  calc_trigo, code, readwrite
	export test_trigo
	import TabCos
	import TabSin
		
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
		
	end