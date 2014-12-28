%macro INTERRUPT_NOERRCODE 1
	global interrupt%1
interrupt%1:
	cli			; Disable interrupts firstly.
	push byte 0		; Push a fake error code.
	push byte 0		; errcode desactivate
	push byte %1	; Push the interrupt number.
	jmp interrupt_gen
%endmacro

	;;  This macro creates a stub for an INTERRUPT which passes it's own
	;;  error code.
%macro INTERRUPT_ERRCODE 1
	global interrupt%1
interrupt%1:
	cli			; Disable interrupts.
	push byte 1		;errcode activer
	push byte %1	; Push the interrupt number
	jmp interrupt_gen
%endmacro


	;; set all symbole for idt handler
%assign i 0
%rep 8
	INTERRUPT_NOERRCODE i
%assign i i + 1
%endrep

INTERRUPT_ERRCODE   8
INTERRUPT_NOERRCODE 9

%assign i 10
%rep 5
	INTERRUPT_ERRCODE i
%assign i i + 1
%endrep

%assign i 15
%rep 17
	INTERRUPT_NOERRCODE i
%assign i i + 1
%endrep

extern interrupt_handler

interrupt_gen:	
	pusha		; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

	mov ax, ds		; Lower 16-bits of eax = ds.
	push eax		; save the data segment descriptor

	mov ax, 0x10  	; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call interrupt_handler

	pop ebx        	; reload the original data segment descriptor
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa		; Pops edi,esi,ebp...
	add esp, 8	; Cleans up the pushed error code and pushed interrupt number
	sti
	iret           	; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

	
