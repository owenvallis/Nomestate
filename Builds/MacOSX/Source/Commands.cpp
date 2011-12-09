/*
  ==============================================================================

    Commands.cpp
    Created: 10 Oct 2011 10:17:05pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "Commands.h"

const String Commands::MIDI_EVENT = "MIDI_EVENT"; 
const String Commands::SIGNAL_MOD = "SIGNAL_MOD"; 
const String Commands::SEND_OSC = "SEND_OSC"; 


Commands::Commands() {
}

Commands::~Commands() {
}
                
void Commands::registerCommand(String name, Command *cmd) {
    COMMAND_LIST.insert( std::pair<String, Command*>(name, cmd) );
}