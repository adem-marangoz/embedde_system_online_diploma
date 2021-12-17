/* linker_script_cortexM3.ld
 * Adem Alnajjar
 *   
 */

MEMORY
{
    FLASH(RX) : ORIGIN = 0x00000000 , l = 512M
    SRAM(RWX) : ORIGIN = 0x20000000 , l = 512M
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
        _E_DATA = . ;
    }> SRAM AT>FLASH
    
    .bss :
    {
        _S_bss = . ;
        *(.bss)
        . = ALIGN(4);
        _E_bss = . ;
    }> SRAM
}
