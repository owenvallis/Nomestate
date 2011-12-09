/*
  ==============================================================================

    Command_MIDITriggerOff.h
    Created: 13 Oct 2011 8:14:32pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __COMMAND_MIDITRIGGEROFF_H_28BAAFCD__
#define __COMMAND_MIDITRIGGEROFF_H_28BAAFCD__

#include "Command.h"
#include "Signal.h"
#include "MIDISender.h" 

class Command_MIDITriggerOff : public Command {
    
public:
    
    Command_MIDITriggerOff(MIDISender &mSender) {
        _mSender = &mSender; 
    }
    
    ~Command_MIDITriggerOff() {}
    
    // Pass by value. Define copy operator. 
    void execute(Signal s) {
        
        // Insert Permission Handling and Signal Conditioning
        
        // _mSender->handleSignal(s); No, redundant. Do more here. 
        
    }
    
private:
    
    MIDISender *_mSender; 
    
};


#endif  // __COMMAND_MIDITRIGGEROFF_H_28BAAFCD__
