/*
  ==============================================================================

    Command_MIDIStream.h
    Created: 13 Oct 2011 8:16:00pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __COMMAND_MIDISTREAM_H_1B726276__
#define __COMMAND_MIDISTREAM_H_1B726276__

#include "Command.h"
#include "Signal.h"
#include "MIDISender.h" 

class Command_MIDIStream : public Command {
    
public:
    
    Command_MIDIStream(MIDISender &mSender) {
        _mSender = &mSender; 
    }
    
    ~Command_MIDIStream() {}
    
    // Pass by value. Define copy operator. 
    void execute(Signal s) {
        
        // Insert Permission Handling and Signal Conditioning
        
        // _mSender->handleSignal(s); No, redundant. Do more here. 
        
        
    }
    
private:
    
    MIDISender *_mSender; 
    
};


#endif  // __COMMAND_MIDISTREAM_H_1B726276__
