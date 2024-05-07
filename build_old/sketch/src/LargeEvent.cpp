#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\src\\LargeEvent.cpp"
#include "Event.h"

#include <Arduino.h>

LargeEvent::LargeEvent() 
{

}

void LargeEvent::addListener(void (*listener)())
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

void LargeEvent::removeListener(void (*listener)()) 
{
    int i = 0;
    //  Checks correspondence in every value of the array, so that listener duplicates (even if bad practice) can be found
    while(i <= lastListenerIndex)
    {
        if(listeners[i] == listener)
        {
            // Scales the array items after the one popped
            // The item corresponding to i will now be the next one
            // Last index is not considered in the loop as new lastIndex for array will always be lastIndex - 1 (one element has been popped), so last element will always be excluded
            for(int j=i; j < lastListenerIndex; j++)
            {
                listeners[j] = listeners[j+1];
            }
            lastListenerIndex--; // lastListenerIndex has ALWAYS to be decremented as one element is always popped out, thus all array is scaled by one and the index of last listener will be reduced
            // There is no need to increase i as the next element to be checked is already in position i as the array is scaled by one starting by i (listeners[i] = listeners[i+1] in first inner cycle execution)
        }
        else { i++; }
    }
}

void LargeEvent::raise() 
{
    Serial.println("Raising all events...");
    for(int i=0; i <= lastListenerIndex; i++)
    {
        Serial.println(rand);
        Serial.println(lastListenerIndex);
        Serial.println((uint16_t)listeners[i+1], HEX);
        (listeners[i])();
    }
}