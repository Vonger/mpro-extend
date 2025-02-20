OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
	ram  : ORIGIN = 0x80000000, LENGTH = 0x200000
}

SECTIONS
{
	.text :
	{
		PROVIDE(__image_start = .);
		PROVIDE(__text_start = .);
		PROVIDE(__extend_start = .);
		start.o (.text)
		*(.text*)
		PROVIDE(__text_end = .);
	} > ram

	.rodata ALIGN(8) :
	{
		PROVIDE(__rodata_start = .);
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
		PROVIDE(__rodata_end = .);
	} > ram

	.data ALIGN(8) :
	{
		PROVIDE(__data_start = .);
		*(.data*)
		. = ALIGN(8);
		PROVIDE(__data_end = .);
		PROVIDE(__image_end = .);
	} > ram

    	.rel.dyn ALIGN(4) : {
		__rel_dyn_start = .;
		*(.rel*)
		__rel_dyn_end = .;
	} > ram

	.bss ALIGN(8) (NOLOAD) :
	{
		PROVIDE(__bss_start = .);
		*(.bss*)
		*(.sbss*)
		*(COMMON)
		PROVIDE(__bss_end = .);
	} > ram
}
