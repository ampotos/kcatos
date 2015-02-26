[GLOBAL switch_to_user_mode]

;;; Stack must look like this:

;;; new EIP	(1)
;;; CS		(2)
;;; EFLAGS	(3)
;;; ESP		(4)
;;; SS		(5)

switch_to_user_mode:
	
	cli
	mov	ebp, esp
	push	ebp
	
	mov	eax, [esp + 16]	; old_esp save
	;; mov	ecx, [esp]	; current ret eip

	
	mov	ecx, [esp + 12]	; new esp
	mov	edx, [esp + 8]	; new eip
	
	mov	eax, 0x20	; 0x20 -> user ds
	or	eax, 0x3	; 0x3 for privilege level 3 (usermode)
	mov	ds, eax
	mov	es, eax
	mov	fs, eax
	mov	gs, eax

	push	eax		; (5)
	push	ecx		; (4)
	pushf			; (3)

	pop	eax		
	or	eax, 0x200	; hack to re-enable interupt
	push	eax
	
	mov	eax, 0x18	; 0x18 -> user cs
	or	eax, 0x3	; priv lvl 3

	push eax		; (2)
	push edx		; (1)
	
	iret
