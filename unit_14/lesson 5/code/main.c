/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/

//_________________________________ Include Files ______________________________
#include "Stm32f10xx_Common.h"
#include "core_cm3.h"
//==============================================================================

//------------------------------ Local Functions -------------------------------
int Set_SVC_Services(int x, int y, int SVCID);
void SVC_services(int* Stack_Frame);
//==============================================================================


//---------------------------- Exception Functions -----------------------------


void PendSv_Handler()
{

}


/*
__attribute__((naked)) function attribute: 
    This attribute tells the compiler that the function is an embedded assembly function. 
    You can write the body of the function entirely in assembly code using __asm statements.
    The compiler does not generate prologue and epilogue sequences for functions with __attribute__((naked)).
    Don't Take memory space when calling becuase is use assembly command
*/
__attribute((naked)) void SVCall_Handler()
{
    /*  TST Instruction :
            These instructions test the value in a register against Operand2. They update the condition flags
            based on the result, but do not write the result to a register.
    */
    __asm(
        "TST lr,0x04    \n\t"
        "ITE EQ         \n\t"
        "mrseq r0,msp   \n\t" // if SPSEL is 0 move MSP register to R0
        "mrsne r0,psp   \n\t" // if SPSEL is 0 move PSP register to R0
        "B SVC_services"      // Brunch to SVC_services function and passing R0 to first argument  
        );
}
//==============================================================================


//_____________________ Generica Function & Data Structure _____________________



void SVC_services(int* Stack_Frame)
{
    // int* Stack_Frame = R0; 
    // Stack_Frame value equal msp value after pushing context
    unsigned char SVC_Number = 0;
    int val1 = 0;
    int val2 = 0;

    SVC_Number = *((unsigned char*)(((unsigned char*)Stack_Frame[6])-2));
    val1 = Stack_Frame[0];
    val2 = Stack_Frame[1];

/*
                                 ___________________
                    val1 ->     |   R0              |  = First argument of Set_SVC_Services
                                |___________________|   
                    val2 ->     |   R1              |  = Seconde argument of Set_SVC_Services
                                |___________________|
                                |   R2              |  
                                |___________________|   
                                |   R3              |
                                |___________________|   
                                |   SP              |
                                |___________________|   
                                |   LR              |
                                |___________________|   
               SVC_Number ->    |   PC              |  = equal arguemnt of SVC instruction |OpCode |Argument|
                                |___________________|                                      | 1byte | 1byte  |
                                |   xPSR            |
                                |___________________|   

*/

    switch (SVC_Number)
    {
        case 1:
            *Stack_Frame = val1 + val2; 
            break;
        case 2:
            *Stack_Frame = val1 - val2; 
            break;
        case 3:
            *Stack_Frame = val1 * val2; 
            break;
        case 4:
            SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;  // Set pending PendSv
            break;
        
        default:
            break;
    }
}



int Set_SVC_Services(int x, int y, int SVCID)
{
    int result = 0;
    switch (SVCID)
    {
        case 1:
            /*
                when execute the SVC exception will push bellow register ro ram by SP
                Push context (xPSR, Return Address, LR(R14), SP(R12), R3, R2, R1, R0)
                xPSR = 
                Return Address = 
                LR = 
                SP = 
                R3 =
                R2 = 0x01
                R1 = 0x66
                R0 = 0x55
             */
            __asm("SVC #0x01"); 
            break;
        case 2:
            __asm("SVC #0x02"); // Push context (xPSR, Return Address, LR(R14), SP(R12), R3, R2, R1, R0)
            break;
        case 3:
            __asm("SVC #0x03"); // Push context (xPSR, Return Address, LR(R14), SP(R12), R3, R2, R1, R0)
            break;
        case 4:
            __asm("SVC #0x04"); // Push context (xPSR, Return Address, LR(R14), SP(R12), R3, R2, R1, R0)
            break;
        default:
            break;
    }

    __asm("mov %0,R0" : "=r" (result) : :);
    return result;
}


int main(void)
{
    int ret = 0;
	ret = Set_SVC_Services(0x55,0x66,1); // R0 = 0x55, R1 = 0x66, R2 = 0x01
	ret = Set_SVC_Services(0x22,0x11,2); // R0 = 0x22, R1 = 0x11, R2 = 0x02
	ret = Set_SVC_Services(0x53,0x64,3); // R0 = 0x53, R1 = 0x64, R2 = 0x03
	ret = Set_SVC_Services(0x57,0x69,4); // R0 = 0x57, R1 = 0x69, R2 = 0x04
    while (1)
    {
        /* code */
    }
    

    return 0;
}

//==============================================================================

    