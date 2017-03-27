/*27-03-17*****************************************************************************************************
***************************************************************************************************************
**                                                                                                           **
**                                                 main.cpp                                                  **
**                                                                                                           **
***************************************************************************************************************
**************************************************************************************************************/

/*#############################################################################################################

Section:                                          ~libs

#############################################################################################################*/

#include "hdmiLCD.h"
#include <string>
#include <iostream>

/*#############################################################################################################

Section:                                          ~main

#############################################################################################################*/

int main()
{

    auto LCD = new HdmiLCD( 0x27 );

    std::string test = "test";
    LCD->init();
    LCD->print( test );
    
    return 0;
}
