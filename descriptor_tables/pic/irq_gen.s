extern interrupt_gen

%macro IRQ 2
	global irq%1
irq%1:
	cli			;disable interrupt
	;; push dword 42		;fake registers normally push by cpu when an interrupt occur
	;; push dword 42
	;; push dword 42
	;; push dword 42
	;; push dword 42
	push byte %1			;push irq number as errcode
	push byte 0
	push byte %2
	jmp interrupt_gen
%endmacro

%assign i 0
%rep 16
	IRQ i, i + 0x20
%assign i i + 1
%endrep
