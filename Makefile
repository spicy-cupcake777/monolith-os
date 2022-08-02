PATH:=${PATH}:${PWD}/tools/bin

all:
	rm -rvf build isodir
	mkdir -pv build isodir/boot/grub
	nasm -felf32 src/multiboot.s -o build/boot.o
	i686-elf-gcc -c src/kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T src/linker.ld -o monolith.elf -ffreestanding -O2 -nostdlib build/*.o
	echo 'menuentry "monolith" {' > grub.cfg
	echo 'multiboot /boot/monolith' >> grub.cfg
	echo '}' >> grub.cfg
	cp grub.cfg isodir/boot/grub
	cp monolith.elf isodir/boot/monolith
	grub-mkrescue -o monolith.iso isodir

clean:
	rm -rvf build monolith.elf isodir monolith.iso grub.cfg

test-qemu: all
	qemu-system-i386 -cdrom monolith.iso
