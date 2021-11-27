/*Adem Alnajjar
*Unit2_lesson2_lab1
*/

ENTRY(reset)
MEMORY
{
    Mem (rwx) : ORIGIN = 0X00000000, LENGTH = 64M
}

SECTIONS
{
    . = 0x10000;
    .startup . :
    {
        startup.o(.text)
    }>Mem
    /*VMA=LAM=mem*/
    .text :
    {
        *(text.o) *(.rodata)
    }>Mem
    /*VMA=LAM=mem*/
    .data :
    {
        *(.data)
    }>Mem
    /*VMA=LAM=mem*/
    .bss :
    {
        *(.bss) *(COMMON)
    }>Mem
    /*VMA=LAM=mem*/
    . = . + 0x1000; /*4KB of Stack Memory*/
    stack_top = .;
}