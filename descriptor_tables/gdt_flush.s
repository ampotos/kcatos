[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp + 4]
	lgdt [eax]
	
	xor eax, eax
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax
	jmp 0x08:.gdt_flush_cs
.gdt_flush_cs:
	ret
