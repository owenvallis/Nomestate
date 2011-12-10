/*
  ==============================================================================

    MessageCenter.h
    Created: 10 Oct 2011 10:01:26pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __MESSAGECENTER_H_1465CB8F__
#define __MESSAGECENTER_H_1465CB8F__

#include "Signal.h"

// + Commands
#include "Commands.h"
// - Commands

class MessageCenter {
    
public:

    MessageCenter(); 
    ~MessageCenter();

    void registerCommands(String name, Command *cmd); 
    bool handleSignal(const Signal&); 
    
private:
    
    Commands _Commands;
            
    JUCE_LEAK_DETECTOR(MessageCenter);    
};


#endif  // __MESSAGECENTER_H_1465CB8F__
