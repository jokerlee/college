; By Joker Lee  
; MASM 5.0
; Vim 7.2
; 12/1/2009
;==============================================
data segment
MAX     EQU 50d
str0    db  '  By Joker Lee, 12/1/2009, MASM5, vim7.2 empowered.',13,10,'$' 
str1    db  'enter the name, "#" to end, max 50 charactors:',13,10,'$' 
str2    db  'enter the id :',13,10,'$' 
str3    db  'enter the score (0,2000):',13,10,'$'
str4    db  'Name    ID      Score','$' 
str5    db  'The average score is : ','$'
str9    db  '======================================================',13,10,'$'
sptr    db  9,'$'
cnt     dw  0                       ; counter of record number
i       dw  0                       ; used as a temp counter
tmp     dw  0
flg     db  0                       ; flag for point
ave     dw  0                       ; store the average score     
nam     db  100*MAX dup(0)
id      db  100*MAX dup(0)
index   dw  100 dup(0)
score   dw  100 dup(0)
buffer  db  MAX dup(0)
data ends
;==============================================
stack segment stack
buttom db 128 dup(0)
stack ends
;==============================================
code segment
;----------------------------------------------

print    macro   str_addr
    push    dx
    push    ax
    lea     dx, str_addr
    ;add     dx, 100h
    mov     ah, 09h
    int     21h
    pop     ax
    pop     dx
    endm

;-----------------------------------------------

main    proc    far
    assume cs:code, ds:data
start:
    push    ds                              ; set ds 
    mov     ax, data
    mov     ds, ax
    xor     ax, ax

    print   str9
    print   str0
    print   str9
    call    input                           ; get input
    call    average                         ; calc average score
    call    sort                            ; sort record by scores
    call    output                          ; print results
    
    pop     ds
    mov     ax, 4c00h
    int     21h
main endp
;------------------------------------------------

newline proc near
    mov     dl, 0ah                         ; \n\r for a new line
    mov     ah, 02h
    int     21h
    mov     dl, 0dh
    mov     ah, 02h
    int     21h
    ret
newline endp
;------------------------------------------------

input   proc    near
    assume cs:code, ds:data
    
    xor     di, di
    mov     cnt, 0

getname:

    print   str1
    ;mov     ah, 0ch                    ; flush the keyboard buffer
    ;mov     al, 0ah
    ;int     21h
    mov     nam[di], 50d                ; buffer[0] = 50
    lea     dx, nam[di]                 ; read string
    mov     ah, 0ah
    int     21h
    call    newline
    
    mov     al, nam[di+2]                 ; if name == '#', end input
    cmp     al, '#'
    jne     addtail 
    jmp     inputend                    ; jump out of range by 6 bytes error
addtail: 
    mov     bl, nam[di+1]                ; add '$'  to the end of string
    xor     bh, bh
    add     bx, 2
    add     bx, di
    mov     nam[bx], '$'

getid:
    print   str2
    mov     id[di], 50d
    lea     dx, id[di]                  ; read string
    mov     ah, 0ah
    int     21h
    call    newline
    
    mov     bl, id[di+1]                ; set the string end with '$'
    xor     bh, bh
    add     bx, 2
    add     bx, di
    mov     id[bx], '$'
    
getscore:
    print   str3
    mov     buffer, 50d                 ; buffer[0] = 50
    mov     buffer[1], 0                ; buffer[0] = 50
    lea     dx, buffer                  ; read string
    mov     ah, 0ah
    int     21h
    call    newline

    mov     tmp, 0
    mov     al, buffer[1]               ; put the length of string
    cmp     al, 0
    je      next
    add     al, 2
    xor     ah, ah                      ;   into stack
    mov     i, ax
    mov     si, 2
    mov     flg, 0
str2int:
    mov     bl, buffer[si]                  ; break loop when meet '\n'
    sub     bh, bh
    cmp     bx, '.'
    jz      point
digit:
    mov     ax, tmp                         ; tmp = tmp * 10 + buffer[si] - '0'
    mov     cx, 10d
    mul     cx
    sub     bl, '0'
    xor     bh, bh
    add     ax, bx
    mov     tmp, ax
    cmp     flg, 1                          ; only read the first digit after
    je      fini                            ;   point, discard others 
    jmp     next
point:
    mov     flg, 1
next:
    inc     si
    cmp     si, i
    jne     str2int

    cmp     flg, 1
    je      fini
    mov     ax, tmp                     ; tmp = tmp * 10
    mov     cx, 10d
    mul     cx
fini:
    mov     bx, cnt
    add     bx, bx                      ; bx = 2*cnt
    mov     score[bx], ax
    inc     cnt
    add     di, MAX
    jmp     getname

inputend:
    ret

input endp
;------------------------------------------------
    
average    proc     near
    assume cs:code, ds:data

    xor     cx, cx
    xor     ax, ax                      ; use ax to store the sum
    cmp     cnt, 0                      ; return if cnt == 0
    jne     sum
    mov     ave, 0
    ret
sum:
    mov     si, cx
    add     si, si
    add     ax, score[si] 
    inc     cx
    cmp     cx, cnt
    jne     sum
    
    xor     dx, dx                      ; calc sum/cnt
    div     cnt
    mov     ave, ax

    ret
average endp
;------------------------------------------------
    
sort    proc    near
    assume cs:code, ds:data

    xor     si, si
    xor     bx, bx
    mov     cx, cnt
    cmp     cx, 0
    jne     initidx
    ret

initidx:
    mov     index[si], si    
    add     si, 2
    loop    initidx
    
    mov     cx, cnt
    dec     cx                          ; if cnt == 1. return without operation
    jnz     loop1
    ret

loop1:
    mov     tmp, cx
    xor     bx, bx
loop2:
    mov     si, index[bx]
    mov     di, index[bx + 2]
    mov     ax, score[si]
    cmp     ax, score[di]
    jge     continue
    mov     ax, index[bx]               ; swap index[bx] and index[bx+2]
    xchg    ax, index[bx + 2]
    mov     index[bx],  ax
continue:
    add     bx, 2
    loop    loop2
    mov     cx, tmp
    loop    loop1 
    ret

sort endp

;--------------------------------------------------

output   proc   near
    assume cs:code, ds:data
    
    mov     ax, data
    mov     ds, ax
    
    xor     si, si
    xor     di, di
    mov     cx, cnt
    cmp     cx, 0
    je      printave
    print   str4
    call    newline
printrecord:
    mov     di, index[si]
    push    di
    mov     ax, di
    shr     ax, 1                           ; ax = ax/2
    mov     bl, 50
    mul     bl                              ; ax = ax * 50
    mov     di, ax
    print   nam[di+2]
    print   sptr
    print   id[di+2]
    print   sptr
    pop     di
    
    mov     bx, score[di]
    call    printnum
    
    add     si, 2
    call    newline
    loop    printrecord
    
printave:    
    print   str5                            ; print the average number
    mov     bx, ave
    call    printnum
    call    newline

    ret
output endp


printnum    proc    near ; out put a number with precision 0.1 in decimal
    push    ax
    push    bx
    push    cx
    push    dx

    mov     ax, bx
    xor     dx, dx
    mov     bx, 10d
    div     bx
    push    dx
    mov     bx, ax
    call    printint
    
    mov     dl, '.'                         ; print point
    mov     ah, 02h
    int     21h
    
    pop     dx
    add     dl, '0'
    mov     ah, 02h
    int     21h    

    pop     dx
    pop     cx
    pop     bx
    pop     ax

    ret
printnum endp
;---------------------------------------------------

printint proc near ; out put a integer in decimal
    push    ax
    push    bx
    push    cx
    push    dx

    mov     flg, 0
    cmp     bx, 0                            ; judge if the num is zero
    jz      zero 
    
lable1:
    mov     ax, bx
    mov     dl, byte ptr 10d
    div     dl                              ; divide by 10
    xchg    ah, al                          ; m
    xor     ah, ah         
    cmp     ax, bx       
    jz      lable2                           ;bx%10 == bx ,
    
    mov     ax, bx        
    mov     dl, byte ptr 10d
    div     dl
    mov     dx, 0
    mov     dl, ah
    inc     flg     
    push    dx
    
    mov     ah, 0
    mov     bx, ax
    jmp     lable1
lable2:
    inc     flg
    push    ax    
    mov     cl, flg
    mov     ch, 0
nextdigit:
    pop     ax
    mov     dl, al
    add     dl, 30h
    mov     ah, 2
    int     21h
    loop    nextdigit
    jmp     exit
zero:
    mov     dl, '0'
    mov     ah, 2
    int     21h
exit:
    pop     dx
    pop     cx
    pop     bx
    pop     ax
    ret
printint endp
;========================================    

code ends
;===================================================
end start
