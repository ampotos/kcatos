[GLOBAL wait_until_the_end_of_your_life]
[GLOBAL is_computer_on]
[GLOBAL is_computer_on_fire]
[GLOBAL kpause]
	
wait_until_the_end_of_your_life:
	cli
	.hang:
	hlt
	jmp .hang
	ret
	
is_computer_on:
	mov eax,0x1
	ret

is_computer_on_fire:
	mov	eax, ebp
	add	eax, ecx
	add	eax, edx
	add	eax, esp
	add	eax, ebp
	add	eax, esi
	add	eax, edi
	
	mov	ecx, 0x1337
	mov	edx, 0
	div	ecx
	mov	ecx, 0x666
	mov	edx, 0
	div	ecx
	cmp	eax, 0x42
	je	.in_fire
	mov	eax, 0
	jmp	.end
	.in_fire:
	mov	eax, 1
	.end:
	ret
