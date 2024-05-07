#include "Event.h"
#include <LCDWIKI_GUI.h>

#include <LCDWIKI_KBV.h>
#include <lcd_mode.h>
#include <lcd_registers.h>
#include <mcu_16bit_magic.h>
#include <mcu_8bit_magic.h>

#ifndef Container_h
#define Container_h

/* 
* A container is an object which stores the LCD and renderEvent used by appended controls.
*/
class Container  
{
    public:
        /// @brief Initialize a new container
        /// @param display pointer to an Adafruit_ILI9341 objects which is the screen controls will be appended to
        /// @param renderEvent the render event responsible of calling every object's render method
        Container(LCDWIKI_KBV* display, LargeEvent* renderEvent)  {
            Container::render = renderEvent;
            Container::myLCD = display;
        }; //  Current LCD for simulation
        /// @brief Initialize a new container 
        Container() {};
        /// The render event responsible of calling every object's render method
        LargeEvent* render;
        /// Pointer to an LCDWIKI_KBV objects which is the screen controls will be appended to
        LCDWIKI_KBV* myLCD; //  Current LCD for simulation

    private:
};

#endif