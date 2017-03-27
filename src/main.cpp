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
    /*
    std::cout << "Main\n";
    HdmiLCD LCD( 0x27 );
    std::cout << "Made LCD\n";
    std::string test = "test";
    LCD.init();
    LCD.print( test );
    std::cout << "Printed\n";
    */

    auto LCD = new HdmiLCD( 0x27 );

    std::string test = "test";
    LCD->init();
    LCD->print( test );
    
    return 0;
}
