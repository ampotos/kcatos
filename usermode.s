[GLOBAL switch_to_user_mode]

;;; Stack must look like this:

;;; new EIP	(1)
;;; CS		(2)
;;; EFLAGS	(3)
;;; ESP		(4)
;;; SS		(5)

switch_to_user_mode:
	
	cli
	
	mov	eax, 0x20	; 0x20 -> user ds
	or	eax, 0x3	; 0x3 for privilege level 3 (usermode)
	mov	ds, eax
	mov	es, eax
	mov	fs, eax
	mov	gs, eax

	mov	ebx, 0x18	; 0x18 -> user cs
	or	ebx, 0x3	; priv lvl 3
	
	push eax		; (5)
	push esp		; (4)
	pushf			; (3)
	push ebx		; (2)
	push next_eip		; (1) TODO: should probably get the next eip from args
	sti
	iret

next_eip:	
	;; Will execute the code after that
	
