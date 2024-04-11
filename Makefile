C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}
DISK_FILE=disk.bin
CC=i686-elf-gcc
CFLAGS= -g
LD=i686-elf-ld
GDB=gdb

%.bin: %.asm
	nasm $< -f bin -o $@
 
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@ # build kernel

%.o: %.asm
	nasm -f elf $<  -o $@

kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} -Ttext 0x1000 -o kernel.bin $^ --oformat binary

assemble: boot/bootloader.bin kernel.bin
	cat $^ > ${DISK_FILE}

boot: assemble
	qemu-system-x86_64 -fda ${DISK_FILE}

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ 

debug: assemble kernel.elf
	qemu-system-i386 -s -fda ${DISK_FILE} &
	# ${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"
	~/src/gdb-frontend/gdbfrontend -G '-ex "target remote localhost:1234" -ex "symbol-file kernel.elf"'
	# nasm -f bin bootloader.asm -o bootloader.bin # build bootloader
	# nasm -f elf kernel_entry.asm -o kernel_entry.o # build kernel_entry (note: as ELF)
	# i686-elf-gcc -ffreestanding -c kernel.c -o kernel.o # build kernel
	# # Use linker to resolve extern in kernel_entry.o
	# i686-elf-ld -o kernel.bin -Ttext 0x1000 kernel.o kernel_entry.o --oformat binary
	# # Concatenate both bootloader and kernel back to back since we are reading right after the first 512bytes
	# cat bootloader.bin kernel.bin > disk.bin
	# # Run 
	# qemu-system-x86_64 -fda disk.bin


