global incr_pit
extern ticks
	
incr_pit:
	push ebp
	mov ebp, esp

	mov eax, ticks
	add DWORD [eax + 4], 1
	jnc end
	add DWORD [eax], 1
end:
	leave
	ret
