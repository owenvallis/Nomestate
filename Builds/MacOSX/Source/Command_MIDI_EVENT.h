/*
  ==============================================================================

    Command_MIDI.h
    Created: 6 Nov 2011 1:29:40am
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __COMMAND_MIDI_H_F94ABE0C__
#define __COMMAND_MIDI_H_F94ABE0C__

#include "Command.h"
#include "Signal.h"
#include "MIDISender.h" 

class Command_MIDI_EVENT : public Command
{
public:
    
    Command_MIDI_EVENT(MIDISender &mSender) {
        _mSender = &mSender; 
    }
    
    ~Command_MIDI_EVENT() {}
    
    // Pass by value. Define copy operator. 
    void execute(Signal s) {
        
        // Insert Permission Handling and Signal Conditioning        
        _mSender->handleSignal(s); //No, redundant. Do more here. 

    }
    
private:
    
    MIDISender *_mSender; 
    
};


#endif  // __COMMAND_MIDI_H_F94ABE0C__
