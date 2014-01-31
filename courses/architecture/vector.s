;*******	 vector plus		********
;---------------------------------------------------------------------
;Program begin at symbol
;requires module INPUT
;read two vectors from stdin and calculate the sum 
;	(type: double,vectorLength 16)
;the result is written to stdout
;The last modified date: 2008-5-10 
;---------------------------------------------------------------------
		
.data
VectorLength:	.word	16
Vector1:	    .word	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
Vector2:	    .word	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
		
Printf1:	    .asciiz 	"Vector ="
Printf2:   	.asciiz		" %f"
		
.align	2
PrintPrompt:	.word	Printf1
PrintPar: 	.word	Printf2
Result:		.space  4
		
.text
		
main:		;**** Print prompt "Vector =" 
		addi	r14,r0,PrintPrompt
		trap	5
				
		lw	r20,VectorLength		;r20<-16	
		addi	r2,r0,0				;r2<-0
		Loop:	
		ld	f10,Vector1(r2)			;load double-precision Floating point to f10 
		ld	f12,Vector2(r2)			;load double-precision Floating point to f12
				
		cvti2d	f0,f10				;convert integer to double into D0(f0:f1)
		cvti2d	f2,f12				;convert integer to double into D1(f2:f3)
				
		addd	f4,f2,f0			;add D2=D0+D1
				
		;**** Finish,write result into stdout
		sd	Result,f4				
		addi	r14,r0,PrintPar
	    trap	5
					
		addi	r2,r2,4				;r2+=4(bytes)
				
		subi	r20,r20,1			;r20--
		bnez	r20,Loop			;branch to Loop if r20 is not equivalent to zero
					
		;**** End
		    trap		0

