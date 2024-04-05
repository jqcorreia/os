[org 0x7c00]
    mov [bios_disk], dl ; store current disk set from bios in dl register

    mov bp, 0x8000 ; set the stack safely away from us
    mov sp, bp

    call clearScreen

    mov cx, 0x0000 ; Row 0, Col 0
    call cursor_goto

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    mov dx, 0xdead
    call print_hex
    call print_nl
    
; _loop:
;     mov ah, 0x00 
;     int 0x16

;     cmp ah, 0x1c ; Enter
;     je _loop

;     mov ah, 0x0e
;     int 0x10

;     jmp _loop


mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000

; Load 2 segments of disk 
mov dh, 2
mov dl, [bios_disk]
call disk_load

; Print a word from first segment
mov dx, [bx + 256]
call print_hex
call print_nl

; Print a word from second segment
mov dx, [bx + 512]
call print_hex
call print_nl

call switch_protected_mode
jmp $

%include "utils.asm"
%include "disk.asm"
%include "gdt.asm"
%include "string.asm"

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROTECTED_MODE
    call print_string_pm

    jmp $


bios_disk: db 0x00
hello: db "Hello, World", 0

MSG_REAL_MODE: db "Running in 16-bit real mode", 0
MSG_PROTECTED_MODE: db "Running in 32-bit protected mode", 0

times 510 - ($ - $$) db 0
dw 0xaa55

times 256 dw 0xdead ; word = 2 bytes, 256 * 2 = 512 bytes == 1 sector!
times 256 dw 0xbeef ; another one


