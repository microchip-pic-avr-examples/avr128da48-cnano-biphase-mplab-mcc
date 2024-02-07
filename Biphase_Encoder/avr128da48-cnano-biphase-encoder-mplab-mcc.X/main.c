 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include <util/delay.h>
#include <stdbool.h>

#define START_BYTE          0xFF    /* Start byte used for clock synch */
#define STOP_BYTE           0x00    /* Start byte used for clock synch */
#define BIPHASE_BAUD_RATE   31250   /* Biphase communication baud rate */
#define GAP_DURATION        (2 * F_CPU / BIPHASE_BAUD_RATE)  

/*
    Main application
*/

int main(void)
{
    bool break_flag = false;
    bool comm_flag = false;
    uint8_t receivedByte;
     
    SYSTEM_Initialize();
    SPI0_Open(HOST_CONFIG);
    while(!SPI0_IsTxReady())
        ;
    SPI0_ByteWrite(START_BYTE); /* Byte sent to calibrate the biphase communication bus */
    
    while (1)
    {
        if(USART1_IsRxReady() == true)
        {   
            receivedByte = USART1_Read();
            
            if(break_flag == true)
            {
                break_flag = false;
                _delay_us(GAP_DURATION);
                while(!SPI0_IsTxReady())
                    ;    
                SPI0_ByteWrite(START_BYTE);
            }
            
            while(!SPI0_IsTxReady())
                ;
            SPI0_ByteWrite(receivedByte);
            comm_flag = true;
        }
        else
        {
            if(comm_flag == true)
            {
                while(!SPI0_IsTxReady())
                    ;
                SPI0_ByteWrite(STOP_BYTE); /* Byte sent to calibrate the biphase communication bus */
                comm_flag = false;
            }
            
            break_flag = true;
        }
    }
}
