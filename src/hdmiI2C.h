/*26-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                                 hdmiI2C.h                                                 **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/

/* By Håkon Hystad, NTNU. Based on http://www.susa.net/wordpress/2012/06/raspberry-pi-pcf8563-real-time-clock-rtc/ */

/* driver to use the HDMI I2C on the raspberry pi 3B */
/* using the BCM2835 datasheet (p.28-) and updating the base address to fit later versions of the pi */

#ifndef _HDMII2C_H_
#define _HDMII2C_H_

/*#############################################################################################################

Section:                                          ~literals

#############################################################################################################*/

// physical addressing
#define IOBASE   0x3F000000
#define I2C_BASE (IOBASE + 0x805000)	// the I2C base for HDMI (BSC2)

// control register p.29
#define C_I2CEN   (1 << 15)	// enable controller
#define C_INTR    (1 << 10)	// interrupt on Rx 
#define C_INTT    (1 << 9)	// interrupt on Tx
#define C_INTD    (1 << 8)	// interrupt on done
#define C_ST      (1 << 7)	// start transfer
#define C_CLEAR   (1 << 4)	// clear FIFO
#define C_READ    1		// read transfer

#define START_READ     C_I2CEN | C_ST | C_CLEAR | C_READ
#define START_WRITE    C_I2CEN | C_ST

// status register p.31
#define S_CLKT   (1 << 9)	// clock stretch timeout
#define S_ERR    (1 << 8)	// ACK error 
#define S_RXF    (1 << 7)	// FIFO full - read under way
#define S_TXE    (1 << 6)	// FIFO empty - write under way
#define S_RXD    (1 << 5)	// data in FIFO
#define S_TXD    (1 << 4)	// FIFO can accept data to transmit
#define S_RXR    (1 << 3)	// FIFO need read (full)
#define S_TXW    (1 << 2)	// FIFO needs write (full)
#define S_DONE   (1 << 1)	// transfer done
#define S_TA     1		// transfer active

#define CLEAR_STATUS    S_CLKT|S_ERR|S_DONE

/*#############################################################################################################

Section:                                          ~macros

#############################################################################################################*/

// register virtual mapping macros
#define I2C_C(addr)        (addr + 0x00)	// control
#define I2C_S(addr)        (addr + 0x04)	// status
#define I2C_DLEN(addr)     (addr + 0x08)	// data length
#define I2C_A(addr)        (addr + 0x0C)	// slave address
#define I2C_FIFO(addr)     (addr + 0x10)	// data FIFO

/*#############################################################################################################

Section:                                          ~libs

#############################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

/*#############################################################################################################

Section:                                          ~declarations

#############################################################################################################*/


    
int mapPeripheral( Peripheral *p );

void i2cWrite( uint8_t msg );

struct Peripheral
{
    uint32_t physical_addr;
    int fd;
    void *map;
    volatile uint32_t *addr
};


#endif// header guard
