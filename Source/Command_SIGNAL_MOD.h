/*
  ==============================================================================

    Command_SIGNAL_MOD.h
    Created: 6 Nov 2011 8:46:26pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __COMMAND_SIGNAL_MOD_H_37F1A076__
#define __COMMAND_SIGNAL_MOD_H_37F1A076__

#include "Command.h"
#include "Signal.h"
#include "SignalModifier.h" 

class Command_SIGNAL_MOD : public Command
{
public:
    
    Command_SIGNAL_MOD(SignalModifier &sigModifier) {
        _sigModifier = &sigModifier; 
    }
    
    ~Command_SIGNAL_MOD() {}
    
    // Pass by value. Define copy operator. 
    void execute(Signal s) {
        
        // Insert Permission Handling and Signal Conditioning        
        _sigModifier->handleSignal(s); //No, redundant. Do more here. 
        
    }
    
private:
    
    SignalModifier *_sigModifier; 
    
};



#endif  // __COMMAND_SIGNAL_MOD_H_37F1A076__
