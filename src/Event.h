#include <Arduino.h>

#ifndef Event_h
#define Event_h

/**
 * An event is an object which stores functions which are called when a class calls a raise.
 * For memory limit reasons, only 5 listeners are subscribable, though this limit can be changed by modifying the hard-coded constant "MAXIMUM_LISTENERS"
 * Listener functions should always be void functions only accepting a void* argument
*/
class Event 
{
    public:
        /// @brief Declares the maximum amount of listeners subscribable to the event. 
        /// Unless it is really necessary, this value should be low to avoid memory problems
        static const int MAXIMUM_LISTENERS = 5; // For memory reasons, there is a maximum available number of listeners per event.
        /// @brief Event constructor
        ///
        Event();
        /// @brief Subscribes a listener void function to the event
        /// @param listener Pointer to listener function
        /// @param arguments Void pointer representing call arguments of the listener function. The function will be called passing those arguments.
        void addListener(void (*listener)(void* args), void* arguments);
        /// @brief Subscribes a listener void function to the event
        /// @param listener Listener function
        void addListener(void (*listener)(void* args));
        /// @brief Removes a listener from the event
        /// @param listener Pointer to listener function to remove
        void removeListener(void (*listener)(void* args));
        /// @brief Raises the event
        ///
        void raise();

    private:
        /// @brief The array of pointers to listener functions.
        /// The length of the array is degtermined by MAXIMUM_LISTENERS constant
        void (*listeners[MAXIMUM_LISTENERS]) (void* args); // An array of pointers to listener functions
        /// @brief The array storing arguments associated to each listener during subscription.
        /// Every function will be called with this argument.
        /// Argument should be in the form void*, so that maximum abstraction of the argument is given
        /// Do note that casting class objects require the static-cast statement
        void* args[MAXIMUM_LISTENERS]; // An array of void pointers to arguments of listener functions
        /// @brief The index of the last stored listener. It is increased before storing a new listener, thus is initialized to -1
        ///
        int lastListenerIndex = -1; // Index of the last listener subscribed to the event
};

/** @brief Event which supports more listeners. By default, the value of maximum listeners is set 10 times higher than a normal event.
 * 
 * An event is an object which stores functions which are called when a class calls a raise.
 * For memory limit reasons, only 5 listeners are subscribable, though this limit can be changed by modifying the hard-coded constant "MAXIMUM_LISTENERS"
 * Listener functions should always be void functions only accepting a void* argument
*/
class LargeEvent
{
    public:
        /// @brief Event constructor
        ///
        LargeEvent();
        /// @brief Subscribes a listener void function to the event
        /// @param listener Pointer to listener function
        /// @param arguments Void pointer representing call arguments of the listener function. The function will be called passing those arguments.
        void addListener(void (*listener)(void* args), void* arguments);
        /// @brief Subscribes a listener void function to the event
        /// @param listener Listener function
        void addListener(void (*listener)(void* args));
        /// @brief Removes a listener from the event
        /// @param listener Pointer to listener function to remove
        void removeListener(void (*listener)(void* args));
        /// @brief Raises the event
        ///
        void raise();

    private:
        /// @brief Declares the maximum amount of listeners subscribable to the event.
        /// By default, for a LargeEvent this value is set 10 times higher than a normal event's one 
        /// Unless it is really necessary, this value should not be modified to avoid memory problems
        static const int MAXIMUM_LISTENERS = 10 * Event::MAXIMUM_LISTENERS; // For memory reasons, there is a maximum available number of listeners per event.
        /// @brief The array of pointers to listener functions.
        /// The length of the array is degtermined by MAXIMUM_LISTENERS constant
        void (*listeners[MAXIMUM_LISTENERS]) (void* args); // An array of pointers to listener functions
        /// @brief The array storing arguments associated to each listener during subscription.
        /// Every function will be called with this argument.
        /// Argument should be in the form void*, so that maximum abstraction of the argument is given
        /// Do note that casting class objects require the static-cast statement
        void* args[MAXIMUM_LISTENERS]; // An array of void pointers to arguments of listener functions
        /// @brief The index of the last stored listener. It is increased before storing a new listener, thus is initialized to -1
        ///
        int lastListenerIndex = -1; // Index of the last listener subscribed to the event
};

#endif