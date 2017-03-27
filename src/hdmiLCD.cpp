/*27-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                                hdmiLCD.cpp                                                **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/
#include "hdmiLCD.h"
#include <iostream>

/*=============================================================================================================

NAME:                                             ~HdmiLCD( constructor )
ARGUMENT(S):
DESCRIPTION: initialize com object with slave address
RETURN:

==============================================================================================================*/

HdmiLCD::HdmiLCD( uint8_t LCDAddr )
    : COM( new HdmiI2C ),
      m_LCDAddr( LCDAddr )
{
    // empty
    std::cout << "Constructor\n";
  
}

/*=============================================================================================================

NAME:                                             ~HdmiLCD( destructor )
ARGUMENT(S):
DESCRIPTION:
RETURN:

==============================================================================================================*/

HdmiLCD::~HdmiLCD()
{
    delete COM;
}

/*=============================================================================================================

NAME:                                             ~setLCDAddr
ARGUMENT(S):
DESCRIPTION: setter
RETURN:

==============================================================================================================*/

void HdmiLCD::setLCDAddr( uint8_t LCDAddr )
{
    m_LCDAddr = LCDAddr;// let COM class handle range check
}

/*=============================================================================================================

NAME:                                             ~setupCOM
ARGUMENT(S):
DESCRIPTION:
RETURN:

==============================================================================================================*/

void HdmiLCD::setupCOM()
{
    std::cout << "setup..";
    COM->setSlaveAddr( m_LCDAddr );
    COM->setup();
    std::cout << "Done\n";
}

/*=============================================================================================================

NAME:                                             ~LCDwrite
ARGUMENT(S):
DESCRIPTION:
RETURN:

==============================================================================================================*/

void HdmiLCD::LCDwrite()
{
    std::cout << "write: " << std::hex << msg << std::dec << std::endl;
    COM->HdmiI2C::write( msg );
}
