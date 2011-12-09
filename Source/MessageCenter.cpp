/*
  ==============================================================================

    MessageCenter.cpp
    Created: 10 Oct 2011 10:01:26pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "MessageCenter.h"

using namespace std; 

MessageCenter::MessageCenter() {
            
}

MessageCenter::~MessageCenter() {}

void MessageCenter::registerCommands(String name, Command *cmd) {
    _Commands.registerCommand(name, cmd);
}

bool MessageCenter::handleSignal(const Signal &s) {

    std::map<String, Command*>::iterator result; 
    
    result = _Commands.COMMAND_LIST.find(s.command);
    
    if (result == _Commands.COMMAND_LIST.end()) {
        DBG("No Command Found"); 
        return false; 
    }
        
    else {
        // Intense logging can occur here, based on Command::Type / ->first
        DBG("Command " + result->first + " found. Executing.");
        result->second->execute(s); 
        return true; 
    }

}