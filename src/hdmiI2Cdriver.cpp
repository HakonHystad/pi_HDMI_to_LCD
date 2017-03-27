/*27-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                             hdmiI2Cdriver.cpp                                             **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/

#include "hdmiI2Cdriver.h"


/*=============================================================================================================

NAME:                                             ~HdmmiI2C(default constructor)
ARGUMENT(S):
DESCRIPTION: default constructr, marks slaveAddress as unvalid
RETURN:

==============================================================================================================*/
HdmiI2C::HdmiI2C()
    : m_sAddr( 0 )
{
    // empty
}


/*=============================================================================================================

NAME:                                             ~HdmiI2C(constructor)
ARGUMENT(S):
DESCRIPTION: constructor, initializes slaveAddr
RETURN:

==============================================================================================================*/

HdmiI2C::HdmiI2C( uint8_t slaveAddr )
    : m_sAddr( slaveAddr )
{
    setup();
}

/*=============================================================================================================

NAME:                                             ~setup
ARGUMENT(S):
DESCRIPTION: finds the register addresses as well as setting the slave address
RETURN: 0 on success, -1 on failure

==============================================================================================================*/

int HdmiI2C::setup()
{
    // map it
    if( mapPeripheral() <0 ) return -1;

    // find register addresses 
    m_reg->C = I2C_C( m_p->addr );
    m_reg->S = I2C_S( m_p->addr );
    m_reg->DLEN = I2C_DLEN( m_p->addr );
    m_reg->A = I2C_A( m_p->addr );
    m_reg->FIFO = I2C_FIFO( m_p->addr );

    // set slave address
    if( m_sAddr>0 )
    {
	*m_reg->A = m_sAddr;
	return 0;
    }

    std::cerr << "No valid slave address set\n";
    return -1;
}

/*=============================================================================================================

NAME:                                             ~write
ARGUMENT(S):
DESCRIPTION: writes a byte over the I2C bus
RETURN:

==============================================================================================================*/

void HdmiI2C::write( uint8_t msg )
{
    *m_reg->DLEN = 8;
    *m_reg->FIFO = msg;

    *m_reg->S = CLEAR_STATUS;
    *m_reg->C = START_WRITE;

    wait();
}

/*=============================================================================================================

NAME:                                             ~setSlaveAddr
ARGUMENT(S):
DESCRIPTION: setter
RETURN:

==============================================================================================================*/

void HdmiI2C::setSlaveAddr( uint8_t slaveAddr )
{
    // I2C uses 7-bit addressing
    if( slaveAddr > 0x7F )
    {
	std::cerr << "Invalid I2C slave address\n";
	return;
    }

    m_sAddr = slaveAddr;
}

/*=============================================================================================================

NAME:                                             ~mapPeripheral
ARGUMENT(S):
DESCRIPTION: maps virtual memory to physical
RETURN: -1 if error

==============================================================================================================*/

int HdmiI2C::mapPeripheral()
{
    // Obtain handle to physical memory
    if (( m_p->fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0)
    {
	std::cerr << "Unable to open /dev/mem\n";
	return -1;
    }

    // map physical memory to virtual memory
    m_p->map = mmap( NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, m_p->fd, m_p->physical_addr );

    if( m_p->map == MAP_FAILED )
    {
	perror( "mmap" );
	return -1;
    }

    m_p->addr = (volatile uint32_t *)m_p->map;

    return m_p->fd;

}

/*=============================================================================================================

NAME:                                             ~wait
ARGUMENT(S):
DESCRIPTION: waits for the status register to clear
RETURN:

==============================================================================================================*/

void HdmiI2C::wait()
{
     //Wait till done, let's use a timeout just in case
    int timeout = 50;
    while( !(*m_reg->S & S_DONE) && --timeout )
    {
	usleep(1000);
    }
	if(timeout == 0) std::cerr << "i2c timeout. Something went wrong.\n";
	
}
