MEMORY 
{
	FLASH  (rx): ORIGIN = 0x08000000, LENGTH = 256K
	EFLASH (rx): ORIGIN = 0x08000000 + 256K - 1, LENGTH = 0
	SRAM   (rw): ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
	.exception_vect :
	{
		_flash_start_ = .;
		KEEP(*(.exception_vect))
	} > FLASH
	
	.text :
	{
		CREATE_OBJECT_SYMBOLS
		*(.text .text.* .gnu.linkonce.t.*)
		*(.plt)
		*(.gnu.warning)
		*(.glue_7t) *(.glue_7) *(.vfp11_veneer)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.gcc_except_table)
		_text_end_ = .;
	} > FLASH
	
	.eflash :
	{
		_flash_end_ = .;
	} > EFLASH
	
	.data : AT(_text_end_)
 	{
 		. = ALIGN(4);
 		_data_start_ = .;
		KEEP(*(.jcr))
		*(.got.plt) *(.got)
		*(.shdata)
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN (8);
		*(.ram)
		*(.ramfunc*)
		 . = ALIGN(4);
		_data_end_ = . ;
  	} > SRAM
  	
  	.rodata : ALIGN (4)
	{
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		
		. = ALIGN(4);
		KEEP(*(.init))
		
		. = ALIGN(4);
		__preinit_array_start = .;
		KEEP (*(.preinit_array))
		__preinit_array_end = .;
		
		. = ALIGN(4);
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		__init_array_end = .;
		
		. = ALIGN(4);
		KEEP(*(.fini))
		
		. = ALIGN(4);
		__fini_array_start = .;
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		__fini_array_end = .;
		
		. = ALIGN(0x4);
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*crtend.o(.ctors))
		
		. = ALIGN(0x4);
		KEEP (*crtbegin.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*crtend.o(.dtors))
		
		*(.init .init.*)
		*(.fini .fini.*)
		
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		PROVIDE_HIDDEN (__fini_array_end = .);
		
		. = ALIGN (8);
		*(.rom)
		*(.rom.b)
		_etext = .;
		/* This is used by the startup in order to initialize the .data secion */
		_sidata = _etext;
	} > FLASH
  	
  	.bss (NOLOAD) :
	{
	 	. = ALIGN(4);
	 	_bss_start_ = . ;
	 	*(.shbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		. = ALIGN (8);
		*(.ram.b)
		. = ALIGN(4);
		_bss_end_ = . ;
		. = ALIGN(8);
		_heap_start_ = .;
		_heap_end_ = ORIGIN(SRAM) + LENGTH(SRAM) - 4K;
		_stack_start_ = _heap_end_ + 8;
		_stack_end_ = ORIGIN(SRAM) + LENGTH(SRAM);
	} > SRAM
  
  	. = ALIGN(4);
  	_end_ = . ;
}