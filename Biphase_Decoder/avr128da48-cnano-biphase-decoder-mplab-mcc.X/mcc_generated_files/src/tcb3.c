/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/


#include "../include/tcb3.h"

/**
 * \brief Initialize tcb interface
 *
 * \return Initialization status.
 */
void (*TCB3_OVF_isr_cb)(void) = NULL;

void TCB3_SetOvfIsrCallback(TCB3_cb_t cb)
{
	TCB3_OVF_isr_cb = cb;
}

void (*TCB3_CAPT_isr_cb)(void) = NULL;

void TCB3_SetCaptIsrCallback(TCB3_cb_t cb)
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

        /**
	 * The Overflow interrupt flag is cleared by writing 1 to it.
	 */
	 if(TCB3.INTFLAGS & TCB_OVF_bm)
        {
            if (TCB3_OVF_isr_cb != NULL)
            {
                (*TCB3_OVF_isr_cb)();
            }

            TCB3.INTFLAGS = TCB_OVF_bm;
        }
	 
}

/**
 * \brief Initialize TCB interface
 */
int8_t TCB3_Initialize()
{
    //Compare or Capture
    TCB3.CCMP = 0x1AF;

    //Count
    TCB3.CNT = 0x00;

    //ASYNC enabled; CCMPINIT disabled; CCMPEN enabled; CNTMODE SINGLE; 
    TCB3.CTRLB = 0x56;

    //DBGRUN disabled; 
    TCB3.DBGCTRL = 0x00;

    //FILTER disabled; EDGE enabled; CAPTEI enabled; 
    TCB3.EVCTRL = 0x11;

    //OVF disabled; CAPT disabled; 
    TCB3.INTCTRL = 0x00;

    //OVF disabled; CAPT disabled; 
    TCB3.INTFLAGS = 0x00;

    //Temporary Value
    TCB3.TEMP = 0x00;

    //RUNSTDBY disabled; CASCADE disabled; SYNCUPD disabled; CLKSEL DIV1; ENABLE enabled; 
    TCB3.CTRLA = 0x01;

    return 0;
}

void TCB3_WriteTimer(uint16_t timerVal)
{
	TCB3.CNT=timerVal;
}

uint16_t TCB3_ReadTimer(void)
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
	TCB3.INTFLAGS &= ~TCB_CAPT_bm;

}

inline void TCB3_ClearOvfInterruptFlag(void)
{
	TCB3.INTFLAGS &= ~TCB_OVF_bm;

}

inline bool TCB3_IsCaptInterruptEnabled(void)
{
        return ((TCB3.INTCTRL & TCB_CAPT_bm) > 0);
}

inline bool TCB3_IsOvfInterruptEnabled(void)
{
        return ((TCB3.INTCTRL & TCB_OVF_bm) > 0);
}


