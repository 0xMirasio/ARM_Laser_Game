	thumb
	area  moncode2, code, readonly
	import TabSig
	import TabCos
	import TabSin
	export dft
	export dft_im
	export dft_re

dft		proc
	push {lr}
	bl dft_re ; on recup re(k) depuis r12
	smull r1, r0, r8, r8 ; calcul de Re(k)^2 dans r1,r0
	push {r0-r1} ; on sauvegarde re(k)^2
	bl dft_im ; calcul de im(k) dans r12
	pop {r0-r1} ; on recuperere re(k)^2
	smlal r1, r0, r8, r8
	pop {pc}
	endp

dft_im         proc
    mov r3, #0 ; début compteur pour la boucle
	mov r8, #0 ; somme init a 0
start_im
    cmp r3, #63
    bne loop_im
    b out_im ; quite la boucle
loop_im
    ;  dans la boucle
	mul r2, r3 , r0 ; indice i*k
	; calcul modulo pour rester dans [0, N-1]
	and r2, r2, #0x003F ; 63 = 0x003F
	; on récupere le sin
	ldr r12, =TabSin
	ldrsh r2, [r12,r2, LSL #1] ; on recup le sin(k*i*2pi/N) dans r2
	; on recupère x(i) 
	ldr r12, =TabSig
	ldrsh r1, [r12, r3, LSL #1] ; on recup le x(i) dans r1
	; conversion r1 r2 en entier pour le calcul
	mla r8, r1, r2, r8 ; r8 = r2*r1 + r8
    add r3, #1 ; on incrémente la boucle
    b start_im
out_im
    bx lr
    endp
    
dft_re         proc
    mov r3, #0 ; début compteur pour la boucle
	mov r8, #0 ; somme init a 0
start_re
    cmp r3, #63
    bne loop_re
    b out_re ; quite la boucle
loop_re
    ;  dans la boucle
	mul r2, r3 , r0 ; indice i*k
	; calcul modulo pour rester dans [0, N-1]
	and r2, r2, #0x003F ; 63 = 0x003F
	; on récupere le cos
	ldr r12, =TabCos
	ldrsh r2, [r12,r2, LSL #1] ; on recup le cos(k*i*2pi/N) dans r2
	; on recupère x(i) 
	ldr r12, =TabSig
	ldrsh r1, [r12, r3, LSL #1] ; on recup le x(i) dans r1
	; conversion r1 r2 en entier pour le calcul
	mla r8, r2, r1, r8 ; r8 = r2*r1 + r8
    add r3, #1 ; on incrémente la boucle
    b start_re
out_re
    bx lr
    endp
    
    
    end