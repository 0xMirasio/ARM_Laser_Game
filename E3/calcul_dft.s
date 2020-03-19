	thumb
	area  moncode2, code, readwrite
	import TabSig
	import TabCos
	import TabSin
	export dft
		
dft		 proc
	ldr r1, =TabSig
	ldr r2, =TabCos
	bx lr
	endp
	
	
	end