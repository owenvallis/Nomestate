/*
  ==============================================================================

    MIDIReceiver.cpp
    Created: 10 Oct 2011 10:02:49pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "MIDIReceiver.h"

MIDIReceiver::MIDIReceiver(MessageCenter& center, MidiIODeviceManager &MidiDeviceManager)
{
    _mCenter = &center;
    _MidiDeviceManager = &MidiDeviceManager;
    
    _MidiDeviceManager->addMidiInputCallback(String::empty, this);
}

MIDIReceiver::~MIDIReceiver()
{
    
}

void MIDIReceiver::handleIncomingMidiMessage (MidiInput *source, const MidiMessage &message)
{	      
    DBG("midi in");
    // is this midi input source enabled
    if(_MidiDeviceManager->isMidiInputEnabled(source->getName()))
    {
        DBG(source->getName());

        if(message.isController() && _MidiDeviceManager->isCcEnabled(source->getName(), true)
           && appProperties->getUserSettings()->getIntValue("midiInputChannel") == message.getChannel())
        {      
            
            DBG(message.getControllerNumber() );
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "RCV_MIDI");
            
            ledStateSignal->addStringArg("/nomestate/grid/led/set");
            // get the x position: LED bumber % 8
            ledStateSignal->addIntArg(message.getControllerNumber() % 8);
            // get the y position: LED number / 8
            ledStateSignal->addIntArg(message.getControllerNumber() / 8);
            // get the LED state: toggleState
            
            int ledState;
            if (message.getControllerValue() > 0) {
                ledState = 1;
            }
            
            ledStateSignal->addIntArg(ledState);
            
            _mCenter->handleSignal(*ledStateSignal); 
        } 
        else if (message.isNoteOn() && _MidiDeviceManager->isNoteEnabled(source->getName(), true)
                 && appProperties->getUserSettings()->getIntValue("midiInputChannel") == message.getChannel())
        {            
            // lets set the color based off MIDI note Velocity
            int MIDIVelocity = message.getVelocity();
            int r = 0;
            int g = 0;
            int b = 0;
            
            if (MIDIVelocity > 0){	
                // red
                if (MIDIVelocity <= 22)
                {				
                    r = 127;
                }
                // yellow
                else if (MIDIVelocity <= 43)
                {
                    r = 127;
                    g = 127;
                }
                // green
                else if (MIDIVelocity <= 64)
                {
                    g = 127;
                }
                // teal
                else if (MIDIVelocity <= 85)
                {
                    g = 127;
                    b = 127;
                }
                // blue
                else if (MIDIVelocity <= 106)
                {
                    b = 127;
                }
                // purple
                else
                {				
                    b = 127;
                    r = 127;				
                }
            }
            
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledColourSignal = new Signal("SEND_OSC", "RCV_MIDI");
            
            ledColourSignal->addStringArg("/nomestate/grid/led/color");
            // get the x position: LED bumber % 8
            ledColourSignal->addIntArg(message.getNoteNumber() % 8);
            // get the y position: LED number / 8
            ledColourSignal->addIntArg(message.getNoteNumber() / 8);
            // get the LED RED: 
            ledColourSignal->addIntArg(r);
            // get the LED GREEN: 
            ledColourSignal->addIntArg(g);
            // get the LED BLUE: 
            ledColourSignal->addIntArg(b);
            
            _mCenter->handleSignal(*ledColourSignal);
            
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "RCV_MIDI");
            
            ledStateSignal->addStringArg("/nomestate/grid/led/set");
            // get the x position: LED bumber % 8
            ledStateSignal->addIntArg(message.getNoteNumber() % 8);
            // get the y position: LED number / 8
            ledStateSignal->addIntArg(message.getNoteNumber() / 8);
            // get the LED state: toggleState
            
            ledStateSignal->addIntArg(1);
            
            _mCenter->handleSignal(*ledStateSignal); 
            
            
        }
        else if (message.isNoteOff() && _MidiDeviceManager->isNoteEnabled(source->getName(), true)
                 && appProperties->getUserSettings()->getIntValue("midiInputChannel") == message.getChannel())
        {             
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "RCV_MIDI");
            
            ledStateSignal->addStringArg("/nomestate/grid/led/set");
            // get the x position: LED bumber % 8
            ledStateSignal->addIntArg(message.getNoteNumber() % 8);
            // get the y position: LED number / 8
            ledStateSignal->addIntArg(message.getNoteNumber() / 8);
            // get the LED state: toggleState
            
            ledStateSignal->addIntArg(0);
            
            _mCenter->handleSignal(*ledStateSignal); 
        }
        
    }
}