global incr_pit
extern g_pit_ticks
	
incr_pit:
	push ebp
	mov ebp, esp

	mov eax, g_pit_ticks
	add DWORD [eax + 4], 1
	jnc end
	add DWORD [eax], 1
end:
	leave
	ret
