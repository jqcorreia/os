; 	AH = 02
; 	AL = number of sectors to read	(1-128 dec.)
; 	CH = track/cylinder number  (0-1023 dec., see below)
; 	CL = sector number  (1-17 dec.)
; 	DH = head number  (0-15 dec.)
; 	DL = drive number (0=A:, 1=2nd floppy, 80h=drive 0, 81h=drive 1)
; 	ES:BX = pointer to buffer


; 	on return:
; 	AH = status  (see INT 13,STATUS)
; 	AL = number of sectors read
; 	CF = 0 if successful
; 	   = 1 if error


; 	- BIOS disk reads should be retried at least three times and the
; 	  controller should be reset upon error detection
; 	- be sure ES:BX does not cross a 64K segment boundary or a
; 	  DMA boundary error will occur
; 	- many programming references list only floppy disk register values
; 	- only the disk number is checked for validity
; 	- the parameters in CX change depending on the number of cylinders;
; 	  the track/cylinder number is a 10 bit value taken from the 2 high
; 	  order bits of CL and the 8 bits in CH (low order 8 bits of track):

; 	  |F|E|D|C|B|A|9|8|7|6|5-0|  CX
; 	   | | | | | | | | | |	`-----	sector number
; 	   | | | | | | | | `---------  high order 2 bits of track/cylinder
; 	   `------------------------  low order 8 bits of track/cyl number
disk_load:
    pusha
    push dx ; Save dx since it will be rewritten

    mov ah, 0x02 ; read sectors function
    mov al, dh ; read dh number of sectors
    mov ch, 0x00 ; cylinder
    mov cl, 0x02 ; sector, 0x01 is bootsector, 0x02+ are the following ones
    mov dh, 0x00 ; head
    ; dl is set by caller and is the disk 

    int 0x13 ; Call interrupt 13h
    jc disk_error
    
    pop dx
    cmp al, dh
    jne sectors_error

    popa
    ret
    
disk_error:
    mov bx, DISK_ERROR
    call print

    mov dl, al
    mov dh, ah
    call print_nl
    call print_hex
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

    jmp disk_loop

disk_loop: jmp $


DISK_ERROR: db "Disk read error!", 0
SECTORS_ERROR: db "Sector read error!", 0
