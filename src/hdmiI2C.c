/*26-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                                 hdmiI2C.c                                                 **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/

#include "hdmiI2C.h"

/*=============================================================================================================

NAME:                                             ~i2cSetup
ARGUMENT(S):
DESCRIPTION: get peripheral data, set slave address
RETURN: Periheral struct in given pointer, and status (-1=error)

==============================================================================================================*/

int i2cSetup( peripheral *p, uint8_t slaveAddr )
{
    if( mapPeripheral( p ) <0 ) return -1;

    *I2C_A( p->addr ) = slaveAddr;// assign slave address

    return 0;
}

    
/*=============================================================================================================

NAME:                                             ~mapPeripheral
ARGUMENT(S):
DESCRIPTION: open the memory mapping
RETURN: file descriptor, exits on failure

==============================================================================================================*/
int mapPeripheral( peripheral *p )
{
    // Obtain handle to physical memory
    if (( p->fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0)
    {
	printf("Unable to open /dev/mem\n");
	return -1;
    }

    // map physical memory to virtual memory
    p->map = mmap( NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, p->fd, p->physical_addr );

    if( p->map == MAP_FAILED )
    {
	perror( "mmap" );
	return -1;
    }

    p->addr = (volatile uint32_t *)p->map;

    return p->fd;
    
}

/*=============================================================================================================

NAME:                                             ~i2cWrite
ARGUMENT(S):
DESCRIPTION: send a byte over i2c
RETURN:

==============================================================================================================*/

void i2cWrite( peripheral *p, uint8_t msg )
{
    *I2C_DLEN( p->addr ) = 8;// sending a byte
    *I2C_FIFO( p->addr ) = msg;// add byte to FIFO

    *I2C_S( p->addr ) = CLEAR_STATUS;// reset status
    *I2C_C( p->addr ) = START_WRITE;

    waitI2CDone( p );

}

/*=============================================================================================================

NAME:                                             ~waitI2CDone
ARGUMENT(S):
DESCRIPTION: checks the status reg until completion and returns
RETURN:

==============================================================================================================*/

void waitI2CDone( peripheral *p )
{
     //Wait till done, let's use a timeout just in case
    int timeout = 50;
    while((!( (*I2C_S( p->addr ) ) & S_DONE) ) && --timeout)
    {
	usleep(1000);
    }
    if(timeout == 0) printf("wait_i2c_done() timeout. Something went wrong.\n");

}
