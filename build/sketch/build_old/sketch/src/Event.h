#line 1 "C:\\Users\\emanu\\OneDrive\\Documenti\\CamplusProgettoLibreriaTFTDebug1\\CamplusUI-TFT-Documentato\\build_old\\sketch\\src\\Event.h"
#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\src\\Event.h"
#include <Arduino.h>

#ifndef Event_h
#define Event_h

class Event 
{
    public:
        static const int MAXIMUM_LISTENERS = 5; // For memory reasons, there is a maximum available number of listeners per event.
        Event();
        void addListener(void (*listener)());
        void removeListener(void (*listener)());
        void raise();

    private:
        void (*listeners[MAXIMUM_LISTENERS]) (); // An array of pointers to listener functions
        int lastListenerIndex = -1; // Index of the last listener subscribed to the event
};

// Event which supports more listeners. By default, the value of maximum listeners is set 10 times higher than a normal event
class LargeEvent
{
    public:
        LargeEvent();
        void addListener(void (*listener)());
        void removeListener(void (*listener)());
        void raise();

    private:
        static const int MAXIMUM_LISTENERS = 10 * Event::MAXIMUM_LISTENERS; // For memory reasons, there is a maximum available number of listeners per event.
        int rand = random(100); //
        void (*listeners[MAXIMUM_LISTENERS]) (); // An array of pointers to listener functions
        int lastListenerIndex = -1; // Index of the last listener subscribed to the event
};

#endif