boot:
	nasm -f bin bootloader.asm -o bootloader.bin # build bootloader
	i686-elf-gcc -ffreestanding -c kernel.c -o kernel.o # build kernel
	nasm -f elf kernel_entry.asm -o kernel_entry.o # build kernel_entry (note: as ELF)
	# Use linker to resolve extern in kernel_entry.o
	i686-elf-ld -o kernel.bin -Ttext 0x1000 kernel.o kernel_entry.o --oformat binary
	# Concatenate both bootloader and kernel back to back since we are reading right after the first 512bytes
	cat bootloader.bin kernel.bin > disk.bin
	# Run 
	qemu-system-x86_64 -fda disk.bin
