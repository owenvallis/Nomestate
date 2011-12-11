/*
  ==============================================================================

    MIDISender.cpp
    Created: 10 Oct 2011 10:02:54pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "MIDISender.h"

MIDISender::MIDISender(MidiIODeviceManager &pMidiIODeviceManager) {
    
    _pDeviceManager = &pMidiIODeviceManager;
}

MIDISender::~MIDISender() {
    
}

void MIDISender::handleSignal(Signal s) {
    
    DBG("MIDISender()::handleSignal(" + s.command + ")."); 
    
    if(s.getArgAsString(0) == "NOTE") {
        if(s.getArgAsInt32(3) > 0) {
            sendNoteOn(s.getArgAsInt32(1), s.getArgAsInt32(2), s.getArgAsInt32(3)); 
        } else {
            sendNoteOff(s.getArgAsInt32(1), s.getArgAsInt32(2)); 
        }
    } else if(s.getArgAsString(0) == "CC") {
        sendCC(s.getArgAsInt32(1), s.getArgAsInt32(2), s.getArgAsInt32(3)); 
    }
    
}

bool MIDISender::sendNoteOn(int channel, int noteNumber, uint8 velocity) {
    
    MidiMessage msg(juce::MidiMessage::noteOn(channel, noteNumber, velocity));
    
    StringArray midiDeviceNames = MidiOutput::getDevices();
    
    for(int midiDevice = 0; midiDevice < midiDeviceNames.size(); midiDevice++) 
    {
        
        if(_pDeviceManager->isNoteEnabled(midiDeviceNames[midiDevice], false))
        {
            ScopedPointer<MidiOutput> MIDI_OUT(MidiOutput::openDevice(midiDevice)); 
    
            MIDI_OUT->sendMessageNow(msg);
        }
    }
    
    return true;
}

bool MIDISender::sendNoteOff(int channel, int noteNumber) {
    
    MidiMessage msg(juce::MidiMessage::noteOff(channel, noteNumber));
    
    StringArray midiDeviceNames = MidiOutput::getDevices();
    
    for(int midiDevice = 0; midiDevice < midiDeviceNames.size(); midiDevice++) 
    {
        
        if(_pDeviceManager->isNoteEnabled(midiDeviceNames[midiDevice], false))
        {
            
            ScopedPointer<MidiOutput> MIDI_OUT(MidiOutput::openDevice(midiDevice)); 
    
            MIDI_OUT->sendMessageNow(msg);
        }
    }
    
    return true;
}

bool MIDISender::sendCC(int channel, int ccNumber, int velocity) {

    
    MidiMessage msg(juce::MidiMessage::controllerEvent (channel, ccNumber, velocity));
    
    StringArray midiDeviceNames = MidiOutput::getDevices();
    
    for(int midiDevice = 0; midiDevice < midiDeviceNames.size(); midiDevice++) 
    {
        
        if(_pDeviceManager->isCcEnabled(midiDeviceNames[midiDevice], false))
        {
            ScopedPointer<MidiOutput> MIDI_OUT(MidiOutput::openDevice(midiDevice)); 
            
            MIDI_OUT->sendMessageNow(msg);
        }
    }

    return true;
}
