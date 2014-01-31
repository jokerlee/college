.data 
Prompt: .asciiz "An integer value >1 : "
PrintfFormat: .asciiz "Factorial=%g\n\n" 
.align 2 
PrintfPar: .word PrintfFormat 
PrintfValue: .space 8 
.text 
.global main 
main: 
;*** Read value from stdin into R1 
addi r1,r0,Prompt 
jal InputUnsigned 
;*** init values 
addi r2,r0,1;将本条语句提前防止冲突 
movi2fp f10,r1 
movi2fp f11,r2
;将本条语句提前，减少左边两个语句的冲突周期 
cvti2d f0,f10 
cvti2d f2,f11 
movd f4,f2 
;*** Break loop if D0 = 1 
Loop: 
led f0,f4 
bfpt Finish 
;*** Multiplication and next loop 
multd f2,f2,f0 
subd f0,f0,f4 
j Loop 
Finish: 
;*** write result to stdout 
sd PrintfValue,f2 
addi r14,r0,PrintfPar 
trap 5 
;*** end 
trap 0 
