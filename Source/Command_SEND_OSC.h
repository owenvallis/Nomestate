/*
  ==============================================================================

    Command_SEND_OSC.h
    Created: 22 Nov 2011 10:07:39am
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __COMMAND_SEND_OSC_H_7BBC4253__
#define __COMMAND_SEND_OSC_H_7BBC4253__

#include "Command.h"
#include "Signal.h"
#include "NetworkSender.h" 

class Command_SEND_OSC : public Command
{
public:
    
    Command_SEND_OSC(NetworkSender &nSender) {
        _nSender = &nSender; 
    }
    
    ~Command_SEND_OSC() {}
    
    // Pass by value. Define copy operator. 
    void execute(Signal s) {
        
        // Insert Permission Handling and Signal Conditioning        
        _nSender->handleSignal(s); //No, redundant. Do more here. 
        
    }
    
private:
    
    NetworkSender *_nSender; 
    
};


#endif  // __COMMAND_SEND_OSC_H_7BBC4253__
