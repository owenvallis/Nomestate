/*
  ==============================================================================

    Command.h
    Created: 10 Oct 2011 10:12:17pm
    Author:  Dimitri Diakopoulos

    Interface definition for a command
 
  ==============================================================================
*/

#ifndef __COMMAND_H_E72C29E__
#define __COMMAND_H_E72C29E__

#include "Signal.h"

class Command {

public:
    
    // Virtual DTOR needed in abstract classes.
    virtual ~Command() {}
    
    virtual void execute(Signal s) = 0; 
    
};


#endif  // __COMMAND_H_E72C29E__
