# monolith-os

A simple hobby OS. Not much to see here yet.

## Build

It requires the build system to have the nasm assembler, GRUB, and xorriso for `grub-mkrescue`.
It also expects to find an i686-elf cross GCC toolchain with binaries in `./tools/bin`. The ISO
can be made using simply `make`, but as you might expect, this requires GNU Make installed.

## Testing

The Makefile contains a test target, `test-qemu`. This will require QEMU with the i386 system.
`make test-qemu` will build the ISO and boot it in QEMU using the ISO as a CD ROM.
