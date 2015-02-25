global io_out
global io_in
	
io_out:
	push ebp
	mov ebp, esp
	
	mov edx, [esp + 8]
	mov eax, [esp + 12]
	out dx, al

	leave
	ret

io_in:
	push ebp
	mov ebp, esp

	xor eax, eax
	
	mov edx, [esp + 8]
	in ax, dx

	leave
	ret
