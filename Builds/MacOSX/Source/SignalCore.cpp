/*
  ==============================================================================

    SignalCore.cpp
    Created: 10 Oct 2011 10:00:33pm
    Author:  Dimitri Diakopoulos
 
    << Follows the Facade Pattern >> 

  ==============================================================================
*/

#include "SignalCore.h"
#include "Command_MIDI_EVENT.h"
#include "Command_SIGNAL_MOD.h"
#include "Command_SEND_OSC.h"


SignalCore::SignalCore() : _mCenter(),
                           _sigModifier(_mCenter),
                           _nRecv(_mCenter)
{    
    
    _mCenter.registerCommands(Commands::MIDI_EVENT, new Command_MIDI_EVENT(_MIDISender));
    _mCenter.registerCommands(Commands::SIGNAL_MOD, new Command_SIGNAL_MOD(_sigModifier));    
    _mCenter.registerCommands(Commands::SEND_OSC, new Command_SEND_OSC(_nSender));

}

SignalCore::~SignalCore() {
    
}
