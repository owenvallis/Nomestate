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

SignalModifier::SignalModifier(MessageCenter &center) : toggleState(0)
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
        
    if(s.command== "SIGNAL_MOD") {
        switch(int(_mpManager->getButtonPropertyContainer(s.getArgAsInt32(0))->propertyTree.getProperty("ButtonMode"))) // this seems ugly
        {
            case 0:         convertToToggle(s); break;
            case 1:         convertToTrigger(s); break;
            case 2:         convertToNote(s); break;

            default:        jassertfalse; break;
        }
    }
    
    s.command = "SEND_OSC";
    
    return true;
}

bool SignalModifier::convertToToggle(Signal &s)
{
    if(s.getArgAsInt32(1))
    {
        toggleState = toggleState ? 0 : 1;
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP midiSignal = new Signal("MIDI_EVENT", "SIG_MOD");
        
        // allow this to set the MIDI Channel
        midiSignal->addStringArg("CC");
        midiSignal->addIntArg(1);
        midiSignal->addIntArg(s.getArgAsInt32(0));
        midiSignal->addIntArg(toggleState);
        
        _mCenter->handleSignal(*midiSignal); 
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "SIG_MOD");
    }
    
    return true;
}

bool SignalModifier::convertToTrigger(Signal &s)
{    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP midiSignal = new Signal("MIDI_EVENT", "SIG_MOD");
    
    // allow this to set the MIDI Channel
    midiSignal->addStringArg("CC");
    midiSignal->addIntArg(1);
    midiSignal->addIntArg(s.getArgAsInt32(0));
    midiSignal->addIntArg(s.getArgAsInt32(1));
    
    DBG(s.getArgAsInt32(1));
    
    _mCenter->handleSignal(*midiSignal); 
    
    return true;
}

bool SignalModifier::convertToNote(Signal &s)
{
    // reference counted Signal ( string command, string origin )
    Signal::SignalP midiSignal = new Signal("MIDI_EVENT", "SIG_MOD");
    
    // allow this to set the MIDI Channel
    midiSignal->addStringArg("NOTE");
    midiSignal->addIntArg(1);
    midiSignal->addIntArg(s.getArgAsInt32(0));
    midiSignal->addIntArg(s.getArgAsInt32(1));
    
    _mCenter->handleSignal(*midiSignal); 
    
    return true;
}

