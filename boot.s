
	MBALIGN     equ  1<<0
	MEMINFO     equ  1<<1
	FLAGS       equ  MBALIGN | MEMINFO
	MAGIC       equ  0x1BADB002	   ; 'magic number' lets bootloader find the header
	CHECKSUM    equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

	section .multiboot
	align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

	section .bootstrap_stack
	align 4
stack_bottom:
	times 16384 db 0
stack_top:

	section .text
	global _start
_start:
	mov esp, stack_top

	extern kernel_main
	extern wait_until_the_end_of_your_life
	call kernel_main

	;; If the kernel_main return, we do a none-active wait.
	call wait_until_the_end_of_your_life
