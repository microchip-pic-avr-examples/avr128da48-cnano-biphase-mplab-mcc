/**
 * TCB3 Generated Driver API Header File
 *
 * @file tcb3.h
 *
 * @defgroup tcb3 TCB3
 *
 * @brief This file contains the API prototypes and custom data types for the TCB3 driver.
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

#ifndef TCB3_H_INCLUDED
#define TCB3_H_INCLUDED

#include <stdint.h>
#include "../system/utils/compiler.h"
#include "./timer_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const struct TMR_INTERFACE TCB3_Interface;

/**
 * @ingroup tcb3
 * @typedef void *TCB3_cb_t
 * @brief Function pointer to callback function called by the TCB. The default value is set to NULL which means that no callback function will be used.
 */
typedef void (*TCB3_cb_t)(void);

/**
 * @ingroup tcb3
 * @brief Registers a callback function to be called at capture event.
 * @param TCB3_cb_t cb - Callback function for capture event.
 * @return None.
 */
void TCB3_CaptureCallbackRegister(TCB3_cb_t cb);

/**
 * @ingroup tcb3
 * @brief Registers a callback function to be called at overflow event.
 * @param TCB3_cb_t cb - Callback function for overflow event.
 * @return None.
 */
void TCB3_OverflowCallbackRegister(TCB3_cb_t cb);

/**
 * @ingroup tcb3
 * @brief Initializes the TCB module
 * @param None.
 * @return None.
 */
void TCB3_Initialize(void);
/**
 * @ingroup tcb3
 * @brief Starts the TCB counter.
 * @param None.
 * @return None.
 */
void TCB3_Start(void);
/**
 * @ingroup tcb3
 * @brief Stops the TCB counter.
 * @param None.
 * @return None.
 */
void TCB3_Stop(void);
/**
 * @ingroup tcb3
 * @brief Enables the capture interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB3_EnableCaptInterrupt(void);
/**
 * @ingroup tcb3
 * @brief Disables the capture interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB3_DisableCaptInterrupt(void);
/**
 * @ingroup tcb3
 * @brief Enables the overflow interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB3_EnableOvfInterrupt(void);
/**
 * @ingroup tcb3
 * @brief Disables the overflow interrupt for the TCB.
 * @param None.
 * @return None.
 */
void TCB3_DisableOvfInterrupt(void);
/**
 * @ingroup tcb3
 * @brief Reads the 16-bit timer value of the TCB.
 * @param None.
 * @return uint16_t
 */
uint16_t TCB3_Read(void);
/**
 * @ingroup tcb3
 * @brief Writes the 16-bit timer value to the TCB. 
 * @param uint16_t timerVal - 16-bit Timer value to write for TCB interface.
 * @return None.
 */
void TCB3_Write(uint16_t timerVal);
/**
 * @ingroup tcb3
 * @brief Checks the Overflow Interrupt flag.
 * @param None.
 * @return bool.
 */
bool TCB3_IsOvfInterruptFlag(void);
/**
 * @ingroup tcb3
 * @brief Checks the Capture Interrupt flag.
 * @param None.
 * @return bool.
 */
bool TCB3_IsCaptInterruptFlag(void);

/**
 * @ingroup tcb3
 * @brief Clears the Capture Interrupt flag.
 * @param None.
 * @return None.
 */
void TCB3_ClearCaptInterruptFlag(void);
/**
 * @ingroup tcb3
 * @brief Checks if the capture interrupt is enabled.
 * @param None.
 * @return None.
 */
bool TCB3_IsCaptInterruptEnabled(void);
/**
 * @ingroup tcb3
 * @brief Clears the Overflow Interrupt flag.
 * @param None.
 * @return None.
 */
void TCB3_ClearOvfInterruptFlag(void);
/**
 * @ingroup tcb3
 * @brief Checks if the overflow interrupt is enabled.
 * @param None.
 * @return None.
 */
bool TCB3_IsOvfInterruptEnabled(void);

/**
 * @ingroup tcb3_normal
 * @brief Performs the tasks to be executed on timer events.
 * @param None.
 * @return None.
 */
void TCB3_Tasks(void);



#ifdef __cplusplus
}
#endif

#endif /* TCB3_H_INCLUDED */