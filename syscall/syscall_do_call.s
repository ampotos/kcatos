[GLOBAL syscall_do_call]
syscall_do_call:
	push	ebp
	mov	ebp, esp
	
	push	dword [ebp + 0xc]
	push	dword [ebp + 0x10]
	push	dword [ebp + 0x14]
	push	dword [ebp + 0x18]	
	push	dword [ebp + 0x1c]

	mov	eax,[ebp+8]
	call	eax
	
	add	esp, 0x18
	leave
	ret
