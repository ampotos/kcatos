
ENTRY(_start)
SECTIONS {
	. = 1M;
	.text BLOCK(4K) : ALIGN(4K)
	{
		code = .;
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		bss = .;
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	end_bss = .;
}
