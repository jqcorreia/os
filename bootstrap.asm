[org 0x7c00]

call clearScreen

mov cx, 0x0000 ; Row 0, Col 0
call cursor_goto

mov bx, hello
call print

_loop:
    mov ah, 0x00 
    int 0x16

    cmp ah, 0x1c ; Enter
    je _loop

    mov ah, 0x0e
    int 0x10

    jmp _loop

%include "utils.asm"

hello:
    db "Hello, World", 0

times 510 - ($ - $$) db 0
dw 0xaa55
