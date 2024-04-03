boot:
	nasm -f bin bootstrap.asm -o bootstrap.bin
	qemu-system-x86_64 bootstrap.bin
