[GLOBAL tss_flush]
tss_flush:
	mov	ax, 0x28	; 0x28 is the index of our tss entry
	or	ax, 0x3		; or 3 for priv lvl 3
	ltr	ax
	ret
