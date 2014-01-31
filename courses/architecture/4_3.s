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
movi2fp f10,r1;与addi r1,r0,Prompt关于r1相关，拉开距离 
cvti2d f0,f10;与上条语句关于f10相关，拉开距离如右 
addi r2,r0,1 
movi2fp f11,r2 
cvti2d f2,f11;与上条语句关于f11冲突 
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
