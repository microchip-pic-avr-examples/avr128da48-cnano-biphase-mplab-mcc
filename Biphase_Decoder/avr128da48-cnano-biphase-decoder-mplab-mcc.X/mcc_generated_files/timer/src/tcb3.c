/**
  * TCB3 Generated Driver File
  *
  * @file tcb3.c
  *
  * @ingroup tcb3
  *
  * @brief This file contains the API implementation for the TCB3 module driver.
  *
  * @version TCB3 Driver Version 1.1.5
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../tcb3.h"

const struct TMR_INTERFACE TCB3_Interface = {
    .Initialize = TCB3_Initialize,
    .Start = TCB3_Start,
    .Stop = TCB3_Stop,
    .PeriodCountSet = TCB3_Write,
    .TimeoutCallbackRegister = NULL,
    .Tasks = NULL
};

void (*TCB3_OVF_isr_cb)(void) = NULL;

void TCB3_OverflowCallbackRegister(TCB3_cb_t cb)
{
	TCB3_OVF_isr_cb = cb;
}

void (*TCB3_CAPT_isr_cb)(void) = NULL;

void TCB3_CaptureCallbackRegister(TCB3_cb_t cb)
{
	TCB3_CAPT_isr_cb = cb;
}

ISR(TCB3_INT_vect)
{
	/* Insert your TCB interrupt handling code */
	/**
	 * The interrupt flag is cleared by writing 1 to it, or when the Capture register
	 * is read in Capture mode
	 */
	if(TCB3.INTFLAGS & TCB_CAPT_bm)
    {
        if (TCB3_CAPT_isr_cb != NULL)
        {
            (*TCB3_CAPT_isr_cb)();
        }

        TCB3.INTFLAGS = TCB_CAPT_bm;
    }
}

void TCB3_Initialize(void)
{
    // CCMP 432; 
    TCB3.CCMP = 0x1B0;

    // CNT undefined; 
    TCB3.CNT = 0x0;

    //ASYNC enabled; CCMPEN disabled; CCMPINIT disabled; CNTMODE SINGLE; 
    TCB3.CTRLB = 0x46;
    
    //DBGRUN disabled; 
    TCB3.DBGCTRL = 0x0;

    //CAPTEI enabled; EDGE enabled; FILTER disabled; 
    TCB3.EVCTRL = 0x11;

    //CAPT enabled; OVF disabled; 
    TCB3.INTCTRL = 0x1;

    //CAPT disabled; OVF disabled; 
    TCB3.INTFLAGS = 0x0;

    //Temporary Value
    TCB3.TEMP = 0x0;

    //CASCADE disabled; CLKSEL DIV1; ENABLE enabled; RUNSTDBY disabled; SYNCUPD disabled; 
    TCB3.CTRLA = 0x1;

}

void TCB3_Start(void)
{
    TCB3.CTRLA |= TCB_ENABLE_bm; /* Start Timer */
}

void TCB3_Stop(void)
{
    TCB3.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */
}

void TCB3_Write(uint16_t timerVal)
{
    TCB3.CNT = timerVal;
}

uint16_t TCB3_Read(void)
{
    uint16_t readVal;

    readVal = TCB3.CNT;

    return readVal;
}

void TCB3_EnableCaptInterrupt(void)
{
    TCB3.INTCTRL |= TCB_CAPT_bm; /* Capture or Timeout: enabled */
}

void TCB3_EnableOvfInterrupt(void)
{
	TCB3.INTCTRL |= TCB_OVF_bm; /* Overflow Interrupt: enabled */
}

void TCB3_DisableCaptInterrupt(void)
{
    TCB3.INTCTRL &= ~TCB_CAPT_bm; /* Capture or Timeout: disabled */
}

void TCB3_DisableOvfInterrupt(void)
{
	TCB3.INTCTRL &= ~TCB_OVF_bm; /* Overflow Interrupt: disabled */
}

inline void TCB3_ClearCaptInterruptFlag(void)
{
    TCB3.INTFLAGS |= TCB_CAPT_bm;
}

inline bool TCB3_IsOvfInterruptFlag(void)
{
	return TCB3.INTFLAGS & TCB_OVF_bm;
}

inline bool TCB3_IsCaptInterruptFlag(void)
{
	return TCB3.INTFLAGS & TCB_CAPT_bm;

}

inline void TCB3_ClearOvfInterruptFlag(void)
{
	TCB3.INTFLAGS |= TCB_OVF_bm;
}

inline bool TCB3_IsCaptInterruptEnabled(void)
{
    return ((TCB3.INTCTRL & TCB_CAPT_bm) > 0);
}

inline bool TCB3_IsOvfInterruptEnabled(void)
{
    return ((TCB3.INTCTRL & TCB_OVF_bm) > 0);
}

