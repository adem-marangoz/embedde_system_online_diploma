/* linker_script_cortexM3.ld
 * Adem Alnajjar
 *   
 */

MEMORY
{
    FLASH(RX) : ORIGIN = 0x08000000 , l = 128K
    SRAM(RWX) : ORIGIN = 0x20000000 , l = 20K
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
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _E_bss = . ;
        . = ALIGN(4);
        . = . +1000;
		_heap_End = .;
        . = ALIGN(4);
        . = . +1000;
        _stack_top = . ;
    }> SRAM
}
