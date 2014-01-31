.data
PrintfFormat:	.asciiz 	"Factorial = %.12f\n\n"
		.align		2
PrintfPar:	.word		PrintfFormat
PrintfValue:	.space		8
Abuffer:	.double         0
Bbuffer:	.double		0
.text
.global   main

main:
	addi   r10,r0,0
	addi   r6,r0,Abuffer
	addi   r7,r0,Bbuffer
LOOP:
	ld     f0,0(r6)
	ld     f2,0(r7)
	
	addd   f4,f0,f2
	
	sd		PrintfValue,f4
	addi		r14,r0,PrintfPar
	trap   5
	
	

finish:	

	trap 0
