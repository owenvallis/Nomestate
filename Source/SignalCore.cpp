/*
 ==============================================================================
 
 SignalCore.cpp
 Created: 10 Oct 2011 10:00:33pm
 Author:  Dimitri Diakopoulos
 
 << Follows the Facade Pattern >> 
 
 ==============================================================================
 */

#include "SignalCore.h"
#include "Command_SEND_MIDI.h"
#include "Command_SIGNAL_MOD.h"
#include "Command_SEND_OSC.h"


SignalCore::SignalCore(MidiIODeviceManager &pMidiIODeviceManager) : _mCenter(),
_sigModifier(_mCenter),
_MIDISender(pMidiIODeviceManager),
_nRecv(_mCenter)
{    
    for (int i = 0; i < 64; i++) {
        
        buttonColours.add(new Value());
        
        buttonColours[i]->referTo ( PropertiesManager::getInstance()->getButtonPropertyContainer(i)->getGroupProperty(Identifier("Colour"),PropertyDescriptor(Identifier("Colour"), "Colour", Identifier("Colour")))); // this is ugly
        
        buttonColours[i]->addListener(this);
    }
    
    DBG(buttonColours.size());
    
    _mCenter.registerCommands(Commands::SIGNAL_MOD, new Command_SIGNAL_MOD(_sigModifier));        
    _mCenter.registerCommands(Commands::SEND_MIDI, new Command_SEND_MIDI(_MIDISender));
    _mCenter.registerCommands(Commands::SEND_OSC, new Command_SEND_OSC(_nSender));
        
}

SignalCore::~SignalCore() {
    for (int i = 0; i < 64; i++) {
        buttonColours[i]->removeListener(this);
    }
}

void SignalCore::valueChanged(Value& value)
{    
    for (int i = 0; i < 64; i++) {
        
        Value *currentValue = buttonColours[i];
        
        if(value.refersToSameSourceAs(*currentValue)) {
            
            Colour currentColour = Colour::fromString(currentValue->toString());
            
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledColourSignal = new Signal("SEND_OSC", "SIG_MOD");
            
            ledColourSignal->addStringArg("/box/grid/led/color");
            // get the x position: LED bumber % 8
            ledColourSignal->addIntArg(i % 8);
            // get the y position: LED number / 8
            ledColourSignal->addIntArg(i / 8);
            // get the LED RED: 
            ledColourSignal->addIntArg(currentColour.getRed() >> 1);
            // get the LED GREEN: 
            ledColourSignal->addIntArg(currentColour.getGreen() >> 1);
            // get the LED BLUE: 
            ledColourSignal->addIntArg(currentColour.getBlue() >> 1);
            
            _mCenter.handleSignal(*ledColourSignal); 
            
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledSetSignal = new Signal("SEND_OSC", "SIG_MOD");
            
            ledSetSignal->addStringArg("/box/grid/led/set");
            // get the x position: LED bumber % 8
            ledSetSignal->addIntArg(i % 8);
            // get the y position: LED number / 8
            ledSetSignal->addIntArg(i / 8);
            // set the LED: 
            ledSetSignal->addIntArg(1);
            
            _mCenter.handleSignal(*ledSetSignal); 
        }
    }
}
