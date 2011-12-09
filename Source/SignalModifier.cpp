/*
 ==============================================================================
 
 SignalModifier.cpp
 Created: 6 Nov 2011 8:47:28pm
 Author:  Owen Vallis
 
 ==============================================================================
 */

#include "SignalModifier.h"

// Forward declaration fun. 
#include "MessageCenter.h"

SignalModifier::SignalModifier(MessageCenter &center) :  lastPressValue(0)
{
    _mCenter = &center;
        
}

SignalModifier::~SignalModifier() {
    
}

void SignalModifier::handleSignal(Signal s) {
    
    DBG("SignalModifier()::handleSignal(" + s.command + ").");
    
    // convert the signal
    convertSignal(s);
    
}

bool SignalModifier::convertSignal(Signal &s)
{
    if(s.command == "SIGNAL_MOD") {
        // only listen to grid/key and /press
        if((int(PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.getProperty("Pressure")) == 0 
            && (s.getArgAsString(0) == "boxgridkey" || s.getArgAsString(0) == "boxpress")) )
        {
            switch(int(PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.getProperty("ButtonMode"))) // this seems ugly
            {
                case 0:         convertToToggle(s); break;
                case 1:         convertToTrigger(s); break;
                case 2:         convertToNote(s); break;
                    
                default:        jassertfalse; break;
            }
        } 
        
        // only listen to grid/pressure if pressure is selected
        else if ((int(PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.getProperty("Pressure")) == 1 
                  && s.getArgAsString(0) == "boxgridpressure") )
        { 
            DBG("pressure");
            switch(int(PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.getProperty("ButtonMode"))) // this seems ugly
            {
                case 0:         convertToTogglePressure(s); break;
                case 1:         convertToTriggerPressure(s); break;
                case 2:         convertToNotePressure(s); break;
                    
                default:        jassertfalse; break;
            }
        }
        s.command = "SEND_OSC";
    }
    
    return true;
}

bool SignalModifier::convertToToggle(Signal &s)
{
    if(s.getArgAsInt32(2))
    {
        int toggleState = PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.getProperty("buttonState") ? 0 : 1;
        
        PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.setProperty("buttonState", toggleState, NULL);
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP midiSignal = new Signal("SEND_MIDI", "SIG_MOD");
        
        // allow this to set the MIDI Channel
        midiSignal->addStringArg("CC");
        midiSignal->addIntArg(1);
        midiSignal->addIntArg(s.getArgAsInt32(1));
        
        
        midiSignal->addIntArg(toggleState * 127);
        
        _mCenter->handleSignal(*midiSignal); 
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
        
        ledStateSignal->addStringArg("/box/grid/led/set");
        // get the x position: LED bumber % 8
        ledStateSignal->addIntArg(s.getArgAsInt32(1) % 8);
        // get the y position: LED number / 8
        ledStateSignal->addIntArg(s.getArgAsInt32(1) / 8);
        // get the LED state: toggleState
        ledStateSignal->addIntArg(toggleState);
        
        _mCenter->handleSignal(*ledStateSignal); 
    }
    
    return true;
}

bool SignalModifier::convertToTrigger(Signal &s)
{    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP midiSignal = new Signal("SEND_MIDI", "SIG_MOD");
    
    midiSignal->addStringArg("CC");
    // TODO: allow this to set the MIDI Channel
    midiSignal->addIntArg(1);
    midiSignal->addIntArg(s.getArgAsInt32(1));
    midiSignal->addIntArg(s.getArgAsInt32(2) * 127);
    
    _mCenter->handleSignal(*midiSignal); 
    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
    
    ledStateSignal->addStringArg("/box/grid/led/set");
    // get the x position: LED bumber % 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) % 8);
    // get the y position: LED number / 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) / 8);
    // get the LED state: toggleState    
    ledStateSignal->addIntArg(s.getArgAsInt32(2));

    _mCenter->handleSignal(*ledStateSignal); 
    
    return true;
}

bool SignalModifier::convertToNote(Signal &s)
{
    // reference counted Signal ( string command, string origin )
    Signal::SignalP midiSignal = new Signal("SEND_MIDI", "SIG_MOD");
    
    // allow this to set the MIDI Channel
    midiSignal->addStringArg("NOTE");
    midiSignal->addIntArg(1);
    midiSignal->addIntArg(s.getArgAsInt32(1));
    midiSignal->addIntArg(s.getArgAsInt32(2) * 127);
    
    _mCenter->handleSignal(*midiSignal); 
    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
    
    ledStateSignal->addStringArg("/box/grid/led/set");
    // get the x position: LED bumber % 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) % 8);
    // get the y position: LED number / 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) / 8);
    // get the LED state: toggleState
    ledStateSignal->addIntArg(s.getArgAsInt32(2));
    
    _mCenter->handleSignal(*ledStateSignal); 
    
    return true;
}

bool SignalModifier::convertToTogglePressure(Signal &s)
{
    int toggleState = 0;
    
    if(s.getArgAsInt32(2) == 0)
    {
        toggleState = PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.getProperty("buttonState") ? 0 : 1;
        
        PropertiesManager::getInstance()->getButtonPropertyContainer(s.getArgAsInt32(1))->propertyTree.setProperty("buttonState", toggleState, NULL);
    }
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP midiSignal = new Signal("SEND_MIDI", "SIG_MOD");
        
        // allow this to set the MIDI Channel
        midiSignal->addStringArg("CC");
        midiSignal->addIntArg(1);
        midiSignal->addIntArg(s.getArgAsInt32(1));
        
        int pressureValue = int((s.getArgAsInt32(2)/1024.00)*127.00);
        midiSignal->addIntArg(jmax(pressureValue, lastPressValue));
        
        _mCenter->handleSignal(*midiSignal);
    
    if(lastPressValue < pressureValue) {
        lastPressValue = pressureValue;
    }
    
        lastPressValue *= toggleState;
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
        
        ledStateSignal->addStringArg("/box/grid/led/set");
        // get the x position: LED bumber % 8
        ledStateSignal->addIntArg(s.getArgAsInt32(1) % 8);
        // get the y position: LED number / 8
        ledStateSignal->addIntArg(s.getArgAsInt32(1) / 8);
        // get the LED state: toggleState
        ledStateSignal->addIntArg(toggleState);
        
        _mCenter->handleSignal(*ledStateSignal); 
    
    return true;
}

bool SignalModifier::convertToTriggerPressure(Signal &s)
{    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP midiSignal = new Signal("SEND_MIDI", "SIG_MOD");
    
    midiSignal->addStringArg("CC");
    // TODO: allow this to set the MIDI Channel
    midiSignal->addIntArg(1);
    midiSignal->addIntArg(s.getArgAsInt32(1));
    int pressureValue = int(((s.getArgAsInt32(2)/900.00)*(s.getArgAsInt32(2)/900.00)*(s.getArgAsInt32(2)/900.00))*127.00);
    midiSignal->addIntArg(pressureValue);
    
    _mCenter->handleSignal(*midiSignal); 
    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
    
    ledStateSignal->addStringArg("/box/grid/led/set");
    // get the x position: LED bumber % 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) % 8);
    // get the y position: LED number / 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) / 8);
    // get the LED state: toggleState
    int state = 0;
    
    if(s.getArgAsInt32(2) > 0) 
        state = 1;
    
    ledStateSignal->addIntArg(state);
    
    _mCenter->handleSignal(*ledStateSignal); 
    
    return true;
}

bool SignalModifier::convertToNotePressure(Signal &s)
{
    // reference counted Signal ( string command, string origin )
    Signal::SignalP midiSignal = new Signal("SEND_MIDI", "SIG_MOD");
    
    // allow this to set the MIDI Channel
    midiSignal->addStringArg("NOTE");
    midiSignal->addIntArg(1);
    midiSignal->addIntArg(s.getArgAsInt32(1));
    int pressureValue = int((s.getArgAsInt32(2)/1024.00)*127.00);
    midiSignal->addIntArg(pressureValue);
    
    _mCenter->handleSignal(*midiSignal); 
    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
    
    ledStateSignal->addStringArg("/box/grid/led/set");
    // get the x position: LED bumber % 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) % 8);
    // get the y position: LED number / 8
    ledStateSignal->addIntArg(s.getArgAsInt32(1) / 8);
    // get the LED state: toggleState
    int state = 0;
    
    if(s.getArgAsInt32(2) > 0) 
        state = 1;
    
    ledStateSignal->addIntArg(state);
    
    _mCenter->handleSignal(*ledStateSignal); 
    
    return true;
}

