[GLOBAL wait_until_the_end_of_your_life]
[GLOBAL is_computer_on]
	
wait_until_the_end_of_your_life:
	cli
	.hang:
	hlt
	jmp .hang
	ret

is_computer_on:
	mov eax,0x1
	ret
