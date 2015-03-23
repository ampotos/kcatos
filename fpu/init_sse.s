	global init_sse

init_sse:
	mov	eax, cr0
	and	ax, 0xFFFB
	or	ax, 0x2
	mov	cr0, eax
	mov	eax, cr4
	or	ax, 3 << 9
	mov	cr4, eax
	fxsave [fxsave_area]
	ret
	
	segment .data
	align 16
fxsave_area:	 TIMES 512 db 0
