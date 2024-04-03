print: 
    pusha 

start:
    mov al, [bx]
    cmp al, 0
    je done

    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp start

done:
    popa
    ret
    
    
clearScreen:
    pusha

    mov ax, 0x0700  ; function 07, AL=0 means scroll whole window
    mov bh, 0x07    ; character attribute = white on black
    mov cx, 0x0000  ; row = 0, col = 0
    mov dx, 0x184f  ; row = 24 (0x18), col = 79 (0x4f)
    int 0x10        ; call BIOS video interrupt

    popa
    ret

cursor_goto:
    pusha

    mov ah, 0x02
    mov bh, 0x00 ; Page number
    mov dx, cx; Move cx as input into dx 
    int 0x10

    popa
    ret

next_line:
    
    
