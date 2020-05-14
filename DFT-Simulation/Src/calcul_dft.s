	thumb
	area  moncode2, code, readonly
	import TabSig
	import TabCos
	import TabSin
	export dft
	export dft_im
	export dft_re

dft		proc
	push {lr, r4-r7}
	push {r0-r1} ; on save K, et TabSig
	bl dft_re ; on recup re(k) depuis r12
	smull r4, r5, r8, r8 ; calcul de Re(k)^2 dans r4,r5
	pop {r0-r1}
	bl dft_im ; calcul de im(k) dans r12
	smlal r4, r5, r8, r8
	mov r0,r5
	pop {pc, r4-r7}
	endp

dft_im         proc
	push {r4-r7}
    mov r3, #0 ; début compteur pour la boucle , i=0
	mov r4, r0 ; on met TabSig
	ldr r5, =TabSin
	mov r6, #0 ; produit ik 
	mov r7, r1 ; k
	mov r8, #0 ; somme init a 0
   
loop_im
    ;  dans la boucle
	ldrsh r1, [r4, r3, LSL #1] ; x(i) dans r1
	ldrsh r2, [r5, r6, LSL #1] ; cos(k*i*2pi/N) dans r2
	
	mla r8, r2, r1, r8 ; r8 = r2*r1 + r8
	add r3, #1 ; on incrémente la boucle
	mul r6, r3, r7 ; on met a jour ik
	and r6, r6, #63	
	cmp r3, #64
    bne loop_im
    b out_im ; quite la boucle
	
out_im
	pop {r4-r7}
    bx lr
    endp

    
dft_re         proc
	push {r4-r7}
    mov r3, #0 ; début compteur pour la boucle , i=0
	mov r4, r0 ; on met TabSig
	ldr r5, =TabCos 
	mov r6, #0 ; produit ik 
	mov r7, r1 ; k
	mov r8, #0 ; somme init a 0
   
loop_re
    ;  dans la boucle
	ldrsh r1, [r4, r3, LSL #1] ; x(i) dans r1
	ldrsh r2, [r5, r6, LSL #1] ; cos(k*i*2pi/N) dans r2
	
	mla r8, r2, r1, r8 ; r8 = r2*r1 + r8
	add r3, #1 ; on incrémente la boucle
	add r6, r6, r7 ; on met a jour ik
	and r6, r6, #63	
	cmp r3, #64
    bne loop_re
    b out_re ; quite la boucle
	
out_re
	pop {r4-r7}
    bx lr
    endp
    
    
    end