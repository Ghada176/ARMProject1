/*
 * SysTick.h
 *
 *  Created on: Jul 26, 2024
 *      Author: Ghada
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "tm4c123gh6pm_registers.h"
#include "std_types.h"


#define Tick_value 15999.999
#define Count_Bit  0x10000


/********************************************************************* *
 *  Service Name: SysTick_Init
 *  Sync/Async: Synchronous
 *  Reentrancy: Non Reentrant
 *  Parameters (in): a_TimeInMilliSeconds - wait time
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to Initialize the timer with certain value a_TimeInMilliSeconds using Interrupts
 **********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);

/********************************************************************* *
 *  Service Name: SysTick_StartBusyWait
 *  Sync/Async: Synchronous
 *  Reentrancy: Non Reentrant
 *  Parameters (in): a_TimeInMilliSeconds - wait time
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to Initialize the timer with certain value a_TimeInMilliSeconds without Interrupts
 **********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

/********************************************************************* *
 *  Service Name: SysTick_Handler
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to be executed when an SysTick exception occurs.
 **********************************************************************/
void SysTick_Handler(void);

/********************************************************************* *
 *  Service Name: SysTick_SetCallBack
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): (*Ptr2Func) (void) - Ptr to the call back function
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler.
 **********************************************************************/
void SysTick_SetCallBack(void (*Ptr2Func) (void));

/********************************************************************* *
 *  Service Name: SysTick_Stop
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to stop the systick timer
 **********************************************************************/
void SysTick_Stop(void);

/********************************************************************* *
 *  Service Name: SysTick_start
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to start/resume the systick timer
 **********************************************************************/
void SysTick_Start(void);

/********************************************************************* *
 *  Service Name: SysTick_Stop
 *  Sync/Async: Synchronous
 *  Reentrancy: Reentrant
 *  Parameters (in): None
 *  Parameters (inout): None
 *  Parameters (out): None
 *  Return value: None
 *  Description: Function to deinitialize  the systick timer
 **********************************************************************/
void SysTick_DeInit(void);


#endif /* SYSTICK_H_ */
