gdt_start:
    ; 8 bytes of 0x0, the null descriptor
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff    ; segment length (bits 0-16)
    dw 0x0000    ; base address (bits 0-15), first one must be 0x00000000
    db 0x00      ; base address (bits 16-23)
    db 10011010b ; flags (P, DPL, S, TYPE) https://en.wikipedia.org/wiki/Global_Descriptor_Table
    db 11001111b ; flags (G, 32bit default, 64bit default, AVL) + last 4 bits of segment length 
    db 0x00      ; final byte of base address (bits 24-31)

gdt_data:
    ; This is overlapped with code for some reason (same base addr, same length)
    dw 0xffff    ; segment length (bits 0-16)
    dw 0x0000    ; base address (bits 0-15), first one must be 0x00000000
    db 0x00      ; base address (bits 16-23)
    db 10010010b ; flags (P, DPL, S, TYPE) since type now is 0 (for data) then all the other 3 bits have different meanings https://en.wikipedia.org/wiki/Segment_descriptor
    db 11001111b ; flags (G, 32bit default, 64bit default, AVL) + last 4 bits of segment length 
    db 0x00      ; final byte of base address (bits 24-31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


[bits 16]
switch_protected_mode:
    cli ; disable interrupts
    lgdt [gdt_descriptor]

    mov eax, cr0 ; get control register (we can't set it directly)
    or eax, 0x1 ; set 1st bit that sets the cpu to 32bit
    mov cr0, eax ; store it

    ; do a far jump, which means a jump to another segment
    ; this clears the CPU pipeline in order to make sure we are in 32 bit mode
    jmp CODE_SEG:init_protected_mode


[bits 32]
init_protected_mode: ; we are now using 32-bit instructions
    mov ax, DATA_SEG ; 5. update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
    mov esp, ebp

    call BEGIN_PM ; 7. Call a well-known label with useful code

    


    
    
    
