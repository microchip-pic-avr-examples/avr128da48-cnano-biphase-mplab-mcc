/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. 
    
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

#include "mcc_generated_files/mcc.h"
#include <util/delay.h>
#include <util/atomic.h>
#include <stdbool.h>
#include "fifo.h"

#define START_BYTE          0xFF    /* Start byte used for clock synch */
#define STOP_BYTE           0x00    /* Start byte used for clock synch */
#define BIPHASE_BAUD_RATE   31250   /* Biphase communication baud rate */
#define GAP_DURATION        (2 * 32000000UL / BIPHASE_BAUD_RATE) 

void SPI0_sendByte(uint8_t data);

int main(void)
{
    uint8_t data;
    bool fifo_is_empty;
    bool break_flag = false;
    bool comm_flag = false;
    
    SYSTEM_Initialize();
    
    FIFO_Init();
    SPI0_sendByte(START_BYTE);  /* Byte sent to calibrate the biphase communication bus */
    
    while (1)
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            fifo_is_empty = FIFO_Get(&data);
        }
        if(fifo_is_empty == false)
        {
            if(break_flag == true)
            {
                break_flag = false;
                _delay_us(GAP_DURATION);
                SPI0_sendByte(START_BYTE);
            }
            SPI0_sendByte(data);
            comm_flag = true;
        }
        else
        {
            if(comm_flag == true)
            {
                SPI0_sendByte(STOP_BYTE);
                comm_flag = false;
            }
            break_flag = true;
        }
    }
}

void SPI0_sendByte(uint8_t data)
{
    while (!(SPI0.INTFLAGS & SPI_DREIF_bm))
    {
        ;
    }
    SPI0.DATA = data;
}

ISR(USART1_RXC_vect)
{
    uint8_t receivedByte;
    receivedByte = USART1_Read();   /* Read the received byte */
    /* Store the received byte in the FIFO buffer */
    if(true == FIFO_Put(receivedByte))
    {  
        /* insert code to signal FIFO buffer full (incoming data loss) */
    }
}