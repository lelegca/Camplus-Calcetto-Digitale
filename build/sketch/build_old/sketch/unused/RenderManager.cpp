#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\build_old\\sketch\\unused\\RenderManager.cpp"
#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\unused\\RenderManager.cpp"
#include "RenderManager.h"
#include <Arduino.h>

#include "Event.h"

RenderManager::RenderManager() 
{
    /*
    if(currentManager == NULL) 
    {
        currentManager = this;
    }
    else
    {
        Serial.println("FATAL ERROR: There is already an instance of RenderManager initialized. Program may crash");
    }
    */
}

void RenderManager::subscribe(void (*renderMethod)())
{
    renderEvent.addListener(renderMethod);
}

void RenderManager::newRender() 
{
    renderEvent.raise();
}