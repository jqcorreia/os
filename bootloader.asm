[org 0x7c00]

mov [bios_disk], dl ; store current disk set from bios

mov bp, 0x8000 ; set the stack safely away from us
mov sp, bp

call clearScreen

mov cx, 0x0000 ; Row 0, Col 0
call cursor_goto

mov bx, hello
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

mov dh, 2
mov dl, [bios_disk]
call disk_load

mov dx, [bx + 256]
call print_hex
call print_nl

mov dx, [bx + 512]
call print_hex
call print_nl

jmp $

%include "utils.asm"
%include "disk.asm"

bios_disk: db 0x00

hello: db "Hello, World", 0

times 510 - ($ - $$) db 0
dw 0xaa55

times 256 dw 0xdead ; word = 2 bytes, 256 * 2 = 512 bytes == 1 sector!
times 256 dw 0xbeef ; another one


