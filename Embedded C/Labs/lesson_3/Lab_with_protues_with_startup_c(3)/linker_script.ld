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
    }> FLASH
    
    .data :
    {
            *(.data)
    }> FLASH
    
    .bss :
    {
            *(.bss)
    }> SRAM
}
