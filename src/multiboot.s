ALXGN	equ	1 << 0
MEMNF	equ	1 << 1
FLAGS	equ	ALXGN | MEMNF
MAGIC	equ	0x1badb002
CHKSM	equ	-(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHKSM


section .bss
stack_bottom:
resb 1024*16
stack_top:


section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

	extern kmain
	call kmain

	cli
.hang:	hlt
	jmp .hang
.end:
