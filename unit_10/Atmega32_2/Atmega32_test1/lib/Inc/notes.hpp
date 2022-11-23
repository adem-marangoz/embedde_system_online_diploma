
////--------------------------------------- 8 Bit Interface ---------------------------------------////
after power on wait for more then 15 ms after VCC rises to 4.5V

0 ' 0 ' 0 ' 0 ' 1 ' 1 ' x ' x ' x ' x     BF cannot be checked before this instruction.

wait fr more than 4.1 ms

0 ' 0 ' 0 ' 0 ' 1 ' 1 ' x ' x ' x ' x     BF cannot be checked before this instruction.

wait for more than 100us

0 ' 0 ' 0 ' 0 ' 1 ' 1 ' x ' x ' x ' x     BF cannot be checked before this instruction.

BF can be checked after the following instructions.
! when BF is not checked, the waiting time between instructions is longer than the execution instuction time (page 45)

Function set . Specify the number of display lines and character font. !the number of display lines and character font cannot be changed after this point
Display off     
Display clear
Entry mode set

0 ' 0 ' 0 ' 0 ' 1 ' 1 ' N ' F ' 0 ' 0
0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 1 ' 0 ' 0 ' 0
0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 1 
0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 0 ' 1 'I/D 'S
////--------------------------------------- 8 Bit Interface ---------------------------------------////
///////////////////////////////////////////////////////////////////////////////////////////////////////





////--------------------------------------- 4 Bit Interface ---------------------------------------////
after power on wait for more then 15 ms after VCC rises to 4.5V
wait for more than 40 ms after VCC rises to 2.7V
wait for more than 15 ms after VCC rises to 4.5V

0 ' 0 ' 0 ' 0 ' 1 ' 1 '     BF cannot be checked before this instruction.
wait for more than 4.1 ms
0 ' 0 ' 0 ' 0 ' 1 ' 1       BF cannot be checked before this instruction.
wait for more than 100us
0 ' 0 ' 0 ' 0 ' 1 ' 1 '
BF can be checked after the following instructions.
! when BF is not checked, the waiting time between instructions is longer than the execution instuction time (page 46)
Function set . Specify the number of display lines and character font. !the number of display lines and character font cannot be changed after this point
Display off     
Display clear
Entry mode set
 
0 ' 0 ' 0 ' 0 ' 1 ' 0
0 ' 0 ' 0 ' 0 ' 1 ' 0
0 ' 0 ' N ' F ' x ' x
0 ' 0 ' 0 ' 0 ' 0 ' 0
0 ' 0 ' 1 ' 0 ' 0 ' 0
0 ' 0 ' 0 ' 0 ' 0 ' 0
0 ' 0 ' 0 ' 0 ' 0 ' 1
0 ' 0 ' 0 ' 0 ' 0 ' 0
0 ' 0 ' 0 ' 1 'I/D' s



////--------------------------------------- 4 Bit Interface ---------------------------------------////
///////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////
////--------------------------------------- Function Description ----------------------------------////
The HD44780U has two 8-bit registers, an instruction register (IR) and a data register (DR).

The IR stores instruction codes, such as display clear and cursor shift, and address information for display
data RAM (DDRAM) and character generator RAM (CGRAM). The IR can only be written from the MPU.

! The DR temporarily stores data to be written into DDRAM or CGRAM and temporarily stores data to be
read from DDRAM or CGRAM. Data written into the DR from the MPU is automatically written into
DDRAM or CGRAM by an internal operation.

! The DR is also used for data storage when reading data
from DDRAM or CGRAM. When address information is written into the IR, data is read and then stored
into the DR from DDRAM or CGRAM by an internal operation

! Data transfer between the MPU is then
completed when the MPU reads the DR. After the read, data in DDRAM or CGRAM at the next address is
sent to the DR for the next read from the MPU. By the register selector (RS) signal, these two registers can
be selected (Table 1).

Busy Flag(BF) : 
    When the busy flag is 1, the HD44780U is in the internal operation mode, and the next instruction will not
    be accepted. When RS = 0 and R/W = 1 (Table 1), the busy flag is output to DB7. The next instruction
    must be written after ensuring that the busy flag is 0.

Address Counter (AC) :
    The address counter (AC) assigns addresses to both DDRAM and CGRAM. When an address of an
    instruction is written into the IR, the address information is sent from the IR to the AC. Selection of either
    DDRAM or CGRAM is also determined concurrently by the instruction.
    After writing into (reading from) DDRAM or CGRAM, the AC is automatically incremented by 1
    (decremented by 1). The AC contents are then output to DB0 to DB6 when RS = 0 and R/W = 1 (Table 1).

    RS      R/W         Operation   
    0       0           IR write as an internal operation (display clear, etc.)
    0       1           Read busy flag (DB7) and address counter (DB0 to DB6)
    1       0           DR write as an internal operation (DR to DDRAM or CGRAM)
    1       1           DR read as an internal operation (DDRAM or CGRAM to DR)



