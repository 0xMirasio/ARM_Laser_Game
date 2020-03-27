	thumb
	area  moncode2, code, readwrite
	import TabSig
	import TabCos
	import TabSin
	export dft
	export dft_im
	export dft_re


dft		proc
	push {lr}
	push {r0}
	push {r1}
	bl dft_im
	ldr r2,[r3] ; on récup la valeur de im(k)
	mul r2,r2 ; calcul de Im(k)^2
	pop {r1}
	pop {r0}
	push {r2}
	bl dft_re
	ldr r2,[r3] ; on récup la valeur de re(k)
	mul r2,r2 ; calcul de Re(k) ^2
	pop {r1} ; on recup la valeur de im(k)^2 sauvegardé
	add r1,r2
	;lsr	r1, #16
	str r1, [r3] ; on la val finale de la dft
	pop {pc}
	endp

dft_im         proc
	push {r1}
    mov r3, #0 ; début compteur pour la boucle
start_im
    cmp r3, #63
    bne loop_im
    b out_im ; quite la boucle
loop_im
    ;  dans la boucle
	mul r2, r3 , r0 ; indice i*k
	; calcul modulo pour rester dans [0, N-1]
	and r2, r2, #0x003F ; 63 = 0x003F
	; on récupere le cos
	mov r1, #2
	mul r2, r1
	ldr r12, =TabSin
	ldrh r2, [r12,r2] ; on recup le cos(k*i*2pi/N) dans r2
	; on recupère x(i) 
	mul r1, r3
	ldr r12, =TabSig
	ldrh r1, [r12, r1] ; on recup le x(i) dans r1
	; conversion r1 r2 en entier pour le calcul
	mul r1, r2 ; calcul a l'instant i
	pop {r2}; adresse de dft_res 
	ldr r12, [r2] ; valeur de dft_res  a l'iteration precendete
	add r12, r1 ; on ajoute a la somme
	str r12, [r2] ; on sazuvegarde la nouvelle valeur de dft_res 
	push {r2}
    add r3, #1 ; on incrémente la boucle
    b start_im
out_im
	pop {r3}
    bx lr
    endp
    

dft_re         proc
	push {r1}
    mov r3, #0 ; début compteur pour la boucle
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
	mov r1, #2
	mul r2, r1
	ldr r12, =TabCos
	ldrh r2, [r12,r2] ; on recup le cos(k*i*2pi/N) dans r2
	; on recupère x(i) 
	mul r1, r3
	ldr r12, =TabSig
	ldrh r1, [r12, r1] ; on recup le x(i) dans r1
	; conversion r1 r2 en entier pour le calcul
	mul r1, r2 ; calcul a l'instant i
	pop {r2}; adresse de dft_res 
	ldr r12, [r2] ; valeur de dft_res  a l'iteration precendete
	add r12, r1 ; on ajoute a la somme
	str r12, [r2] ; on sazuvegarde la nouvelle valeur de dft_res 
	push {r2}
    add r3, #1 ; on incrémente la boucle
    b start_re
out_re
	pop {r3} ; on sort de la stack la valeur de dft_res dans r3
    bx lr
	endp
    
    
    end