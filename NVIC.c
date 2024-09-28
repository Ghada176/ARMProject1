/*
 * NVIC.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Administrator
 */

#include "NVIC.h"

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
//no base priority access?
    if(IRQ_Num<=31)
        NVIC_EN0_REG |= (1<<IRQ_Num); //0=>portA unlike the vector number

    else if(IRQ_Num > 31 && IRQ_Num<=63)
        NVIC_EN1_REG |= (1<<(IRQ_Num %32));

    else if (IRQ_Num > 63 && IRQ_Num<=95)
        NVIC_EN2_REG |= (1<<(IRQ_Num %64));

    else if (IRQ_Num > 95 && IRQ_Num<=127)
           NVIC_EN3_REG |= (1<<(IRQ_Num %96));

    else if (IRQ_Num > 127 && IRQ_Num<=138)
           NVIC_EN4_REG |= (1<<(IRQ_Num %128));
    else
    {
        //error;
    }

}
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{

        if(IRQ_Num<=31)
            NVIC_DIS0_REG |= (1<<IRQ_Num); //0=>portA unlike the vector number

        else if(IRQ_Num > 31 && IRQ_Num<=63)
            NVIC_DIS1_REG |= (1<<(IRQ_Num %32));

        else if (IRQ_Num > 63 && IRQ_Num<=95)
            NVIC_DIS2_REG |= (1<<(IRQ_Num %64));

        else if (IRQ_Num > 95 && IRQ_Num<=127)
               NVIC_DIS3_REG |= (1<<(IRQ_Num %96));

        else if (IRQ_Num > 127 && IRQ_Num<=138)
               NVIC_DIS4_REG |= (1<<(IRQ_Num %128));
        else
        {
            //error;
        }
}

//This function only hndle IRQ: interrupts starts from vector num 16 and up. so, Systick isn't included
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
    if ((IRQ_Num % 4) == 0)
        {
            NVIC_PRI_REG(IRQ_Num) = (NVIC_PRI_REG(IRQ_Num) & ~(SEC0_PRIORITY_MASK)) | (IRQ_Priority << SEC0_PRIORITY_BITS_POS);
        }
        else if ((IRQ_Num - 1) % 4 == 0)
        {
            NVIC_PRI_REG(IRQ_Num) = (NVIC_PRI_REG(IRQ_Num) & ~(SEC1_PRIORITY_MASK)) | (IRQ_Priority << SEC1_PRIORITY_BITS_POS);
        }
        else if ((IRQ_Num - 2) % 4 == 0)
        {
            NVIC_PRI_REG(IRQ_Num) = (NVIC_PRI_REG(IRQ_Num) & ~(SEC2_PRIORITY_MASK)) | (IRQ_Priority << SEC2_PRIORITY_BITS_POS);
        }
        else if ((IRQ_Num - 3) % 4 == 0)
        {
            NVIC_PRI_REG(IRQ_Num) = (NVIC_PRI_REG(IRQ_Num) & ~(SEC3_PRIORITY_MASK)) | (IRQ_Priority << SEC3_PRIORITY_BITS_POS);
        }


}

void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{


       switch(Exception_Num) {
               case EXCEPTION_RESET_TYPE :
                   //dnth
               break;
               case EXCEPTION_NMI_TYPE:
                   //dnth
               break;
               case EXCEPTION_HARD_FAULT_TYPE:
                   //dnth
               break;
               case EXCEPTION_MEM_FAULT_TYPE:
                   NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
               break;
               case EXCEPTION_BUS_FAULT_TYPE:
                   NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
               break;
               case EXCEPTION_USAGE_FAULT_TYPE:
                   NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
               break;
               case EXCEPTION_SVC_TYPE:
                   //dnth
               break;
               case EXCEPTION_DEBUG_MONITOR_TYPE:
                   //dnth
               break;
               case EXCEPTION_PEND_SV_TYPE:
                   //dnth
               break;
               case EXCEPTION_SYSTICK_TYPE:
                   SYSTICK_CTRL_REG   |= 0x02; //just enable
               break;
               default:
                   //error
                   break;
       }


}
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num) {
                  case EXCEPTION_RESET_TYPE:
                      //dnth
                  break;
                  case EXCEPTION_NMI_TYPE:
                      //dnth
                  break;
                  case EXCEPTION_HARD_FAULT_TYPE:
                      //dnth
                  break;
                  case EXCEPTION_MEM_FAULT_TYPE:
                      NVIC_SYSTEM_SYSHNDCTRL &= ~(MEM_FAULT_ENABLE_MASK);
                  break;
                  case EXCEPTION_BUS_FAULT_TYPE:
                      NVIC_SYSTEM_SYSHNDCTRL &= ~(BUS_FAULT_ENABLE_MASK);
                  break;
                  case EXCEPTION_USAGE_FAULT_TYPE:
                      NVIC_SYSTEM_SYSHNDCTRL &= ~(USAGE_FAULT_ENABLE_MASK);
                  break;
                  case EXCEPTION_SVC_TYPE:
                      //dnth
                  break;
                  case EXCEPTION_DEBUG_MONITOR_TYPE:
                      //dnth
                  break;
                  case EXCEPTION_PEND_SV_TYPE:
                      //dnth
                  break;
                  case EXCEPTION_SYSTICK_TYPE:
                      SYSTICK_CTRL_REG   &= ~(0x02); //just disable
                  break;
                  default:
                      //error
                      break;
          }


}
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    switch(Exception_Num) {
                      case EXCEPTION_RESET_TYPE:
                          //dnth
                      break;
                      case EXCEPTION_NMI_TYPE:
                          //dnth
                      break;
                      case EXCEPTION_HARD_FAULT_TYPE:
                          //dnth
                      break;
                      case EXCEPTION_MEM_FAULT_TYPE:
                          /* Assign priority level 1 to the MemManage Fault Exception */
                          NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~(MEM_FAULT_PRIORITY_MASK)) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
                      break;
                      case EXCEPTION_BUS_FAULT_TYPE:
                          NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~(BUS_FAULT_PRIORITY_MASK)) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
                      break;
                      case EXCEPTION_USAGE_FAULT_TYPE:
                          NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~(USAGE_FAULT_PRIORITY_MASK)) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
                      break;
                      case EXCEPTION_SVC_TYPE:
                          NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~(SVC_PRIORITY_MASK)) | (Exception_Priority << SVC_PRIORITY_BITS_POS);

                      break;
                      case EXCEPTION_DEBUG_MONITOR_TYPE:
                          NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~(DEBUG_MONITOR_PRIORITY_MASK)) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
                      break;
                      case EXCEPTION_PEND_SV_TYPE:
                          NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~(PENDSV_PRIORITY_MASK)) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
                      break;
                      case EXCEPTION_SYSTICK_TYPE:
                          NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~(SYSTICK_PRIORITY_MASK)) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
                      break;
                      default:
                          //error
                          break;
              }


}
