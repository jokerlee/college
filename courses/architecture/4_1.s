.data 
;*** Data for Read-Trap 
ReadBuffer: .space 80 
ReadPar: .word 0,ReadBuffer,80 
;*** Data for Printf-Trap 
PrintfPar: .space 4 
SaveR2: .space 4 
SaveR3: .space 4 
SaveR4: .space 4 
SaveR5: .space 4 

.text 
.global InputUnsigned 
InputUnsigned: 
;*** save register contents 
sw SaveR2,r2 
sw SaveR3,r3 
sw SaveR4,r4 
sw SaveR5,r5 
;*** Prompt 
sw PrintfPar,r1 
addi r14,r0,PrintfPar 
trap 5 
;*** call Trap-3 to read line 
addi r14,r0,ReadPar 
trap 3 
;*** determine value 
addi r2,r0,ReadBuffer 
addi r1,r0,0 
addi r4,r0,10 
Loop: 
;*** read digits to end of line 
lbu r3,0(r2) 
seqi r5,r3,10
;与上条语句关于r3冲突，拉开距离，如右

bnez r5,Finish;与上条语句关于r5冲突 
subi r3,r3,48 
multu r1,r1,r4 
add r1,r1,r3;与上条语句关于r1冲突，拉开距离，将下条语句提到本条语句之前 
addi r2,r2,1 
j Loop

Finish: 
;***restore old register 
;*** contents 
lw r2,SaveR2 
lw r3,SaveR3 
lw r4,SaveR4 
lw r5,SaveR5 
jr r31 

