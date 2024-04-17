[org 0x7c00]
KERNEL_OFFSET equ 0x1000
    mov [bios_disk], dl ; store current disk set from bios in dl register

    mov bp, 0x9000 ; set the stack safely away from us
    mov sp, bp

    call clearScreen

    mov cx, 0x0000 ; Row 0, Col 0
    call cursor_goto

    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel
    call switch_protected_mode
    jmp $

load_kernel:
    mov bx, MSG_KERNEL_LOAD
    call print
    call print_nl

    mov bx, KERNEL_OFFSET 

    ; Load 2 segments of disk 
    mov dh, 31
    mov dl, [bios_disk]
    call disk_load
    ret

%include "boot/utils.asm"
%include "boot/disk.asm"
%include "boot/gdt.asm"
%include "boot/string.asm"

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROTECTED_MODE
    call print_string_pm
    call KERNEL_OFFSET

    jmp $


bios_disk: db 0x00

MSG_REAL_MODE: db "Running in 16-bit real mode", 0
MSG_PROTECTED_MODE: db "Running in 32-bit protected mode", 0
MSG_KERNEL_LOAD: db "Loading Kernel", 0

times 510 - ($ - $$) db 0
dw 0xaa55



