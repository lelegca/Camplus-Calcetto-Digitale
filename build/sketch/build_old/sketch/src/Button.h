#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\build_old\\sketch\\src\\Button.h"
#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\src\\Button.h"
#include "Container.h"

#ifndef Button_h
#define Button_h

class Button 
{
    public:
        Button();
        Button(int x, int y) {
            X = x;
            Y = y;
        };
        void append(Container container2);
        void setX(int x);
        void setY(int y);
        static void doSomething();
        Container container;

    private:
        int X;
        int Y;
};

#endif