#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\src\\Event.cpp"
#include "Event.h"

#include <Arduino.h>

Event::Event() 
{

}

void Event::addListener(void (*listener)(void* args), void* arguments)
{
    if(lastListenerIndex < MAXIMUM_LISTENERS - 1)
    {
        lastListenerIndex++;
        Event::listeners[lastListenerIndex] = listener;
        Event::args[lastListenerIndex] = arguments;
    }
    else
    {
        Serial.println("Reached maximum number of listeners! Listener method will not be subscribed to event");
    }
}

void Event::addListener(void (*listener)(void* args))
{
    if(lastListenerIndex < MAXIMUM_LISTENERS - 1)
    {
        lastListenerIndex++;
        listeners[lastListenerIndex] = listener;
    }
    else
    {
        Serial.println("Reached maximum number of listeners! Listener method will not be subscribed to event");
    }
}

void Event::removeListener(void (*listener)(void* args)) 
{
    int i = 0;
    //  Checks correspondence in every value of the array, so that listener duplicates (even if bad practice) can be found
    while(i <= lastListenerIndex)
    {
        if(listeners[i] == listener)
        {
            // Scales the array items after that one element has been popped, so that listeners are stored continously.
            // The item corresponding to i will be replaced by the next one and so on until the end of the loop
            // Last index is not considered in the loop as new lastIndex for array will always be lastIndex - 1 (one element has been popped), so last element will always be excluded
            for(int j=i; j < lastListenerIndex; j++)
            {
                listeners[j] = listeners[j+1];
                args[j] = args[j+1];
            }
            lastListenerIndex--; // lastListenerIndex has ALWAYS to be decremented as one element is always popped out, thus all array is scaled by one and the index of last listener will be reduced
            // There is no need to increase i as the next element to be checked is already in position i as the array is scaled by one starting by i (listeners[i] = listeners[i+1] in first inner cycle execution)
        }
        else { i++; }
    }
}

void Event::raise() 
{
    Serial.println("Raising all events...");
    for(int i=0; i <= lastListenerIndex; i++)
    {
        (listeners[i])(args[i]);
    }
}