#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\src\\Container.h"
#include "Event.h"
#include <Adafruit_ILI9341.h>

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
        Container(Adafruit_ILI9341* display, LargeEvent* renderEvent)  {
            Container::render = renderEvent;
            Container::myLCD = display;
        }; //  Current LCD for simulation
        /// @brief Initialize a new container 
        Container() {};
        /// The render event responsible of calling every object's render method
        LargeEvent* render;
        /// Pointer to an Adafruit_ILI9341 objects which is the screen controls will be appended to
        Adafruit_ILI9341* myLCD; //  Current LCD for simulation

    private:
};

#endif