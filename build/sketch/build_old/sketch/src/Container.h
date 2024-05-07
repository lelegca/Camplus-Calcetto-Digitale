#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\build_old\\sketch\\src\\Container.h"
#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\src\\Container.h"
#include "Event.h"
#include <Adafruit_ILI9341.h>

#ifndef Container_h
#define Container_h

class Container  
{
    public:
        Container(Adafruit_ILI9341 display, LargeEvent renderEvent)  {
            Container::render = renderEvent;
            Container::myLCD = display;
        }; //  Current LCD for simulation
        Container() {};
        //inline LargeEvent getRender() { return render; };
        LargeEvent render;

    private:
        Adafruit_ILI9341 myLCD {Adafruit_ILI9341(0,0,0,0,0,0)}; //  Current LCD for simulation
};

#endif