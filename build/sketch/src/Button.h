#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\src\\Button.h"
#include "Container.h"

#ifndef BLACK
#define BLACK   0x0000
#endif

#ifndef WHITE
#define WHITE   0xFFFF
#endif

#ifndef Button_h
#define Button_h

/*
* @brief A button is a graphical element representing a clickable label.
* Note: in the current version of the library, click method is still not implemented.
*/
class Button 
{
    public:
        Button();
        Button(int x, int y, int width, int height) {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        };
        Button(int x, int y, int width, int height, uint16_t color) {
            X = x;
            Y = y;
            Width = width;
            Height = height;
            Color = color;
        };
        enum Shape {Rectangular, Circular};
        void append(Container* container); // Appends the button to a container and raises a render event
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setColor(uint16_t color);
        void setText(String text);
        void setTextColor(uint16_t color);
        void setTextSize(uint8_t size);
        void setShape(Shape buttonShape);
        void hide();
        void show();
        inline bool isHidden() {return hidden;};
        void render(); // Raises a render event to update the button
        void tick(); // Executes button tick operations such as checking for click

    private:
        Container* container;

        static void renderDelegate(void* args);

        int X = 0;
        int Y = 0;
        int Width = 0;
        int Height = 0;
        uint16_t Color = BLACK;
        uint16_t textColor = WHITE;
        uint8_t textSize = 11;
        String text = "";
        bool hidden = false;
        Shape buttonShape = Shape::Rectangular;

        void checkClick();
};

#endif