all: floppy.img 

floppy.img: kernel.bin boot.bin
	cat boot.bin kernel.bin /dev/zero | dd bs=512 count=2880 of=floppy.img

loader.o: loader.asm
	nasm -f elf loader.asm -o loader.o

kernel.bin: kernel.elf
	objcopy -R .note -R .comment -S -O binary kernel.elf kernel.bin

kernel.elf: loader.o main.c video.c ports.c
	gcc -m32  -ffreestanding -fno-builtin -nostdlib -c *.c
	ld -melf_i386 -Ttext 0x1000 -o kernel.elf loader.o main.o video.o ports.o

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

clean:
	rm -f *.o
	rm -f *~
	rm -f *.elf
	rm -f *.bin
	rm -f floppy.img

test: floppy.img
	virtualbox --startvm test
