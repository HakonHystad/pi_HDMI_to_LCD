/*27-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                                hdmiLCD.cpp                                                **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/
#include "hdmiLCD.h"

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
    COM->setSlaveAddr( m_LCDAddr );
    COM->setup();
}

/*=============================================================================================================

NAME:                                             ~LCDwrite
ARGUMENT(S):
DESCRIPTION:
RETURN:

==============================================================================================================*/

void HdmiLCD::LCDwrite()
{
    COM->write( msg );
}
