#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\src\\Button.cpp"
#include "Button.h"
#include "Container.h"
#include <Arduino.h>

Button::Button() 
{
    Serial.println("Button constructor reached!");
}

void Button::setX(int x) 
{
    Button::X = x;
    container.render.raise();
}

void Button::setY(int y)
{
    Button::Y = y;
}

void onRender() 
{
    Serial.println("Render Method");
    Button::doSomething();
}

void Button::append(Container container2) 
{
    container = container2;
    container.render.addListener(&onRender);
    container.render.raise();
    Serial.println("Hello World!");
}

static void Button::doSomething() {

}

