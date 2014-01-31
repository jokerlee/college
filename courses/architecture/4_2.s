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
lbu r3,0(r2);提到循环之外 
Loop: 
;*** read digits to end of line 
seqi r5,r3,10 
subi r3,r3,48
;将本条语句提前消除关于r5的冲突 
bnez r5,Finish 
multu r1,r1,r4 
addi r2,r2,1;这条语句拉开了上条语句和下条语句的距离，减少因r1相关引起的停顿 
add r1,r1,r3 
lbu r3,0(r2);置于循环末尾 
j Loop 

Finish: 
;***restore old register 
;*** contents 
lw r2,SaveR2 
lw r3,SaveR3 
lw r4,SaveR4 
lw r5,SaveR5 
jr r31 
