#include "Button.h"
#include "Container.h"
#include <Arduino.h>
#include <math.h>
#include <string.h>

Button::Button() 
{
    Serial.println("Button constructor reached!");
}

void Button::setX(int x) 
{
    Button::X = x;
    //container->render->raise(); //DEBUG LINE
}

void Button::setY(int y)
{
    Button::Y = y;
}

void Button::setWidth(int width)
{
    Button::Width = width;
}

void Button::setHeight(int height)
{
    Button::Height = height;
}

void Button::setColor(uint16_t color)
{
    Button::Color = color;
}

void Button::setTextColor(uint16_t color)
{
    Button::textColor = color;
}

void Button::setTextSize(uint8_t size)
{
    Button::textSize = size;
}

void Button::setText(String text)
{
    Button::text = text;
}

void Button::setShape(Shape buttonShape)
{
    Button::buttonShape = buttonShape;
}

// Triggered by render event. It redirects to the all subscribed buttons istances' render methods
static void Button::renderDelegate(void* args) 
{
    static_cast<Button*>(args)->render();
    Serial.println("Render Method");

}

// Appends the button to a container and raises a render event
void Button::append(Container* container) 
{
    Button::container = container;
    container->render->addListener(&renderDelegate, this);
    container->render->raise();
    Serial.println("Hello World!");
}

void Button::hide() 
{
    hidden = true;
}

void Button::show()
{
    hidden = false;
}

// Updates the button by rendering it
void Button::render()
{
    Serial.println("Hello World! I'm in render method");

    if(!hidden) 
    {
        // Creates base rectangle
        switch(buttonShape) {
            case Shape::Rectangular:
                container->myLCD->Fill_Rect(X, Y, Width, Height, Color); // Uses current library for TFT
                break;
            
            case Shape::Circular:
                int16_t Radius = (int16_t) sqrt(pow((int16_t)Width/2, 2) + pow(((int16_t)Height/2),2));
                container->myLCD->Fill_Circle((int16_t)(X+Width/2), (int16_t)(Y+Height/2), Radius);
                break;

            default:
                container->myLCD->Fill_Rect(X, Y, Width, Height, Color); // Uses current library for TFT
                break;
        }

        // Calculates center-aligned text cursor position

        // Cursor X
        int16_t cursorX = (int16_t)X; // Center-aligned text cursor X
        // Tries to align to center the text, textSize in pixel is calculated by multiplying by 5 textSize in width and by 10 textSize in height. If textSize is bigger than width, cursorX will be equal to X to maximize space available
        if(textSize * 5 * (text.length()) <= Width) {
            cursorX = (int16_t)(X + (Width - textSize * 5 * (text.length())) / 2);
        }

        // Cursor Y
        int16_t cursorY = (int16_t)(Y + (Height/2) - textSize * 10 / 2); // Center-aligned text cursor Y

        // Sets text properties
        container->myLCD->Set_Text_colour(textColor);
        container->myLCD->Set_Text_Size(textSize);
        // Prints button text
        char* text_array = text.c_str();
        container->myLCD->Print((uint8_t*)text_array, cursorX, cursorY);
    }

}

void Button::tick() 
{
    checkClick();
}

void Button::checkClick() 
{
    // Check click logic to be added
}

