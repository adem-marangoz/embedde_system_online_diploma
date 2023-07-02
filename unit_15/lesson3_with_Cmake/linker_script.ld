/* linker_script_cortexM3.ld
 * Adem Alnajjar
 *   
 */
_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* end of "RAM" Ram type memory */


MEMORY
{
    FLASH(RX) : ORIGIN = 0x08000000 , LENGTH = 128K
    SRAM(RWX) : ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        *(.vectors*)
        *(.text*)
        *(.rodata)
        _E_text = . ;
    }> FLASH
    
    .data :
    {
        _S_DATA = . ;
        *(.data)
        *(.data.*)
        _E_DATA = . ;
    }> SRAM AT>FLASH
    
    .bss :
    {
        _S_bss = . ;
        __bss_start__ = _S_bss;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _E_bss = . ;
        __bss_end__ = _E_bss;
        . = ALIGN(4);
        . = . +1000;
		_heap_End = .;
        . = ALIGN(4);
        . = . +1000;
        _stack_top = . ;
    }> SRAM
}
