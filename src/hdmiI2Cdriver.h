/*27-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                              hdmiI2Cdriver.h                                              **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/

/* A driverclass from userspace to utilize the I2C bus of the raspberry pi (3B) HDMI port
 * 
 * References: 	-BCM2835 manual (updating the base address to fit 3B)
 * 		-Some implementation from http://www.susa.net/wordpress/2012/06/raspberry-pi-pcf8563-real-time-clock-rtc/
 */

#ifndef _HDMII2CDRIVER_H_
#define _HDMII2CDRIVER_H_

/*#############################################################################################################

Section:                                          ~literals

#############################################################################################################*/

// physical addressing
#define IOBASE	0x3F000000
#define BSC0	0x205000
#define BSC1	0x804000
#define BSC2	0x805000
#define I2C_BASE (IOBASE + BSC0)	// the I2C base for HDMI (BSC2)

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
#define I2C_A(addr)        (addr + 0x0c)	// slave address
#define I2C_FIFO(addr)     (addr + 0x10)	// data FIFO

/*#############################################################################################################

Section:                                          ~libs

#############################################################################################################*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>

/*#############################################################################################################

Section:                                          ~definitions

#############################################################################################################*/

struct Peripheral
{
    uint32_t physical_addr;
    int fd;
    void *map;
    volatile uint32_t *addr;
};

struct Registers
{
    volatile uint32_t *C;
    volatile uint32_t *S;
    volatile uint32_t *DLEN;
    volatile uint32_t *A;
    volatile uint32_t *FIFO;
};

/* Usage: 
 * 1. set slave address
 * 2. run setup
 * 3. write
 * (1-2 can be done by constructor)
 */

class HdmiI2C
{
public:

    HdmiI2C();
    HdmiI2C( uint8_t slaveAddr );
    ~HdmiI2C();

    int setup();
    void write( uint8_t msg );

    void setSlaveAddr( uint8_t slaveAddr );

private:

    /*-------------------------------------- functions  ---------------------------------------*/
    int mapPeripheral();
    void wait();

    /*-------------------------------------- variables  ---------------------------------------*/
    uint8_t m_sAddr;
    Peripheral *m_p;
    Registers *m_reg;
    
};


#endif// header guard
