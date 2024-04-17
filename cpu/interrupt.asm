[extern isr_handler]

; Common ISR code
isr_common_stub: 
    ; 1. Save CPU state
	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds ; Lower 16-bits of eax = ds.
	push eax ; save the data segment descriptor
	mov ax, 0x10  ; kernel data segment descriptor, defined as the 2nd segment in GDT which is 16 (0x10) bytes down
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
    ; 2. Call C handler
	call isr_handler
	
    ; 3. Restore state
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8 ; Cleans up the pushed error code and pushed ISR number
	sti
	iret ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

isr0:
    cli
    push byte 0
    push byte 0

    jmp isr_common_stub

    ret

isr1:
    cli
    push byte 1
    push byte 0

    jmp isr_common_stub

    ret

isr2:
    cli
    push byte 2
    push byte 0

    jmp isr_common_stub

    ret
isr3:
    cli
    push byte 3
    push byte 0

    jmp isr_common_stub

    ret
isr4:
    cli
    push byte 4
    push byte 0

    jmp isr_common_stub

    ret
isr5:
    cli
    push byte 5
    push byte 0

    jmp isr_common_stub

    ret
isr6:
    cli
    push byte 6
    push byte 0

    jmp isr_common_stub

    ret
isr7:
    cli
    push byte 7
    push byte 0

    jmp isr_common_stub

    ret
isr8:
    cli
    push byte 8
    push byte 0

    jmp isr_common_stub

    ret
isr9:
    cli
    push byte 9
    push byte 0

    jmp isr_common_stub

    ret
isr10:
    cli
    push byte 10
    push byte 0

    jmp isr_common_stub

    ret
isr11:
    cli
    push byte 11
    push byte 0

    jmp isr_common_stub

    ret
isr12:
    cli
    push byte 12
    push byte 0

    jmp isr_common_stub

    ret
isr13:
    cli
    push byte 13
    push byte 0

    jmp isr_common_stub

    ret
isr14:
    cli
    push byte 14
    push byte 0

    jmp isr_common_stub

    ret
isr15:
    cli
    push byte 15
    push byte 0

    jmp isr_common_stub

    ret
isr16:
    cli
    push byte 16
    push byte 0

    jmp isr_common_stub

    ret
isr17:
    cli
    push byte 17
    push byte 0

    jmp isr_common_stub

    ret
isr18:
    cli
    push byte 18
    push byte 0

    jmp isr_common_stub

    ret
isr19:
    cli
    push byte 19
    push byte 0

    jmp isr_common_stub

    ret
isr20:
    cli
    push byte 20
    push byte 0

    jmp isr_common_stub

    ret
isr21:
    cli
    push byte 21
    push byte 0

    jmp isr_common_stub

    ret
isr22:
    cli
    push byte 22
    push byte 0

    jmp isr_common_stub

    ret
isr23:
    cli
    push byte 23
    push byte 0

    jmp isr_common_stub

    ret
isr24:
    cli
    push byte 24
    push byte 0

    jmp isr_common_stub

    ret
isr25:
    cli
    push byte 25
    push byte 0

    jmp isr_common_stub

    ret
isr26:
    cli
    push byte 26
    push byte 0

    jmp isr_common_stub

    ret
isr27:
    cli
    push byte 27
    push byte 0

    jmp isr_common_stub

    ret
isr28:
    cli
    push byte 28
    push byte 0

    jmp isr_common_stub

    ret
isr29:
    cli
    push byte 29
    push byte 0

    jmp isr_common_stub

    ret
isr30:
    cli
    push byte 30
    push byte 0

    jmp isr_common_stub

    ret
isr31:
    cli
    push byte 31
    push byte 0

    jmp isr_common_stub

    ret
