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


#ifndef TCB3_H_INCLUDED
#define TCB3_H_INCLUDED

#include "../utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TCB3_cb_t)(void);
void TCB3_SetCaptIsrCallback(TCB3_cb_t cb);
void TCB3_SetOvfIsrCallback(TCB3_cb_t cb);
int8_t TCB3_Initialize();
void TCB3_EnableCaptInterrupt(void);
void TCB3_DisableCaptInterrupt(void);
void TCB3_EnableOvfInterrupt(void);
void TCB3_DisableOvfInterrupt(void);
uint16_t TCB3_ReadTimer(void);
void TCB3_WriteTimer(uint16_t timerVal);
void TCB3_ClearCaptInterruptFlag(void);
bool TCB3_IsCaptInterruptEnabled();
void TCB3_ClearOvfInterruptFlag(void);
bool TCB3_IsOvfInterruptEnabled();

#ifdef __cplusplus
}
#endif

#endif /* TCB3_H_INCLUDED */