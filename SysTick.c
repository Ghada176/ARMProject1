/*
 * SysTick.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Administrator
 */

#include "SysTick.h"

//extern uint32 Count;
static  void (*PtrCallBack)(void) = NULL_PTR;    //why not in h?

void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    //should I check if the user intered a num > 1sec?
    //15999.999*a_TimeInMilliSeconds = reload;
       SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
       SYSTICK_RELOAD_REG  = (Tick_value*a_TimeInMilliSeconds);        /* Set the Reload value with the number of counts needed  */
       SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */
       /* Configure the SysTick Control Register
        * Enable the SysTick Timer (ENABLE = 1)
        * Disable SysTick Interrupt (INTEN = 0)  //will be done by a function
        * Choose the clock source to be System Clock (CLK_SRC = 1) */
       SYSTICK_CTRL_REG   |= 0x07;
       //set priority; will be done  by a separate function;
       SysTick_Start();
}

void SysTick_StartBusyWait (uint16 a_TimeInMilliSeconds)
{
    SYSTICK_CTRL_REG    = 0; /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = (Tick_value*a_TimeInMilliSeconds); /* Set the Reload value with the number of counts needed  */
    SYSTICK_CURRENT_REG = 0; /* Clear the Current Register value */
    SYSTICK_CTRL_REG   |= 0x05;
    SysTick_Start();

}

void SysTick_Handler (void)
{
    if(PtrCallBack!= NULL_PTR) //check if the the call back pointer has been set
    {
        (*PtrCallBack)();
    }
}

// A Function to set the call back pointer with the upper layer function pointer
void SysTick_SetCallBack ( void (*Ptr2Func)(void) )
{
    PtrCallBack = Ptr2Func;
}

// A function to stop the timer
void SysTick_Stop(void) //  could it be implemented by the enable bit?
{
 //   Count = SYSTICK_CURRENT_REG; //save the current register state
 //   SYSTICK_CURRENT_REG= 0; //write any value to clear the count bit; NOT SURE
    SYSTICK_CTRL_REG    &= ~(1<<0); //set the enable bit to 0


}
void SysTick_Start(void)
{
    /*
    if(Count != 0)
    {
    SYSTICK_RELOAD_REG = Count;
   Count=0;
    }
    */

                  /* Configure the SysTick Control Register
                  * Enable the SysTick Timer (ENABLE = 1)
                  * Disable SysTick Interrupt (INTEN = 0)
                  * Choose the clock source to be System Clock (CLK_SRC = 1) */
           SYSTICK_CTRL_REG    |= 0x01; //redundant
           while(!(SYSTICK_CTRL_REG & Count_Bit)); //check if the count bit becomes 1




}

void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG=0;
    SYSTICK_RELOAD_REG=0;
    SYSTICK_CURRENT_REG=0;
    PtrCallBack= NULL_PTR;
}



