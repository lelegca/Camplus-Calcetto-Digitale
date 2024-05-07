#line 1 "C:\\Users\\emanu\\arduino-workspace\\CamplusUI-TFT\\src\\RenderManager.h"
#ifndef RenderManager_h
#define RenderManager_h
#endif

#include "Event.h"

class RenderManager 
{
    public:
        RenderManager();
        //static inline RenderManager *getRender() { return currentManager; }; // Returns current RenderManager instance pointer
        void subscribe(void (*renderMethod)()); // Subscribes a method to renderEvent
        void newRender(); // Raises a new render event
        

    private:
        //static RenderManager *currentManager; // Current instance pointer
        LargeEvent renderEvent; // Render Event

};