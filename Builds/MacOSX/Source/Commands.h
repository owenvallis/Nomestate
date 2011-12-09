/*
  ==============================================================================

    Commands.h
    Created: 10 Oct 2011 10:17:05pm
    Author:  Dimitri Diakopoulos

    TODO: Refactor this into a singleton 
 
  ==============================================================================
*/

#ifndef __COMMANDS_H_BFE68D89__
#define __COMMANDS_H_BFE68D89__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Command.h"
#include <map>
#include <utility>

class Commands {
    
public:     
    
    Commands(); 
    ~Commands(); 
    
    static const String SIGNAL_MOD;
    
    static const String SEND_OSC;
    
    static const String MIDI_EVENT;
    static const String MIDI_KILL;
    
    static const String CLOCK_START;
    static const String CLOCK_STOP;
    static const String CLOCK_CHANGE_BPM;
    static const String CLOCK_CHANGE_QUANTIZE;
    
    static const String CLIENT_SPEAK;
    static const String CLIENT_READY;
    
    // We'll see how fast this is
    std::map<String, Command*> COMMAND_LIST;
    
    void registerCommand(String, Command *); 
    
};


#endif  // __COMMANDS_H_BFE68D89__
