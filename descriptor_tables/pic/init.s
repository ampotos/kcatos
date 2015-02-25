%define SLAVE_NEW 0x28
%define MASTER_NEW 0x20	
	
%define PIC_1    0x20 		;master
%define PIC_1_C PIC_1
%define PIC_1_D (PIC_1_C + 1)
	
%define PIC_2   0xA0		;slave
%define PIC_2_C PIC_2
%define PIC_2_D (PIC_2_C + 1)

%define WAIT_IO out 0x80, al   ;use for wait the end of the i/o operation to synchronize old cpu

	global init_irq
init_irq:
	
	push ebp
	mov ebp, esp
	
	push eax
	push edx

	xor eax, eax
	xor edx, edx

	in ax, PIC_1_D
	push ax
	in ax, PIC_2_D
	push ax
	
	mov al, 0x11 	;send init sequence to both pic
	mov dx, PIC_1_C
	out dx, al
	WAIT_IO
	mov dx, PIC_2_C
	out dx, al
	WAIT_IO
	
	mov al, MASTER_NEW	;setup new vector for master pic
	mov dx, PIC_1_D
	out dx, al
	WAIT_IO

	mov al, SLAVE_NEW	;setup new vector for slave pic
	mov dx, PIC_2_D
	out dx, al
	WAIT_IO

	mov al, 4		;tell master pic where is the slave (irq2)
	mov dx, PIC_1_D
	out dx, al
	WAIT_IO

	mov al, 2		;tell slave his cascade identity (use for linking slave and master)
	mov dx, PIC_2_D
	out dx, al
	WAIT_IO

	mov al, 1		;set mode to master
	mov dx, PIC_1_D
	out dx, al
	WAIT_IO

	mov dx, PIC_2_D		;set mode to slave
	out dx, al
	WAIT_IO

	pop ax
	mov dx, PIC_2_D
	out dx, al
	WAIT_IO
	pop ax
	mov dx, PIC_1_D
	out dx, al
	WAIT_IO
	
	pop edx
	pop eax

	leave
	ret
