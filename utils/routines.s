global kpause
global get_flags
	
kpause:
	.hang:
	hlt
	jmp .hang
	ret

get_flags:
	pushf
	pop eax
	ret
