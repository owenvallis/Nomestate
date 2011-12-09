/*
  ==============================================================================

    MIDISender.cpp
    Created: 10 Oct 2011 10:02:54pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "MIDISender.h"

MIDISender::MIDISender() {
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
    
    ScopedPointer<MidiOutput> MIDI_OUT(MidiOutput::openDevice(0)); 
    
    MIDI_OUT->sendMessageNow(msg);
    
    return true;
}

bool MIDISender::sendNoteOff(int channel, int noteNumber) {
    MidiMessage msg(juce::MidiMessage::noteOff(channel, noteNumber));
    
    ScopedPointer<MidiOutput> MIDI_OUT(MidiOutput::openDevice(0)); 
    
    MIDI_OUT->sendMessageNow(msg);
    
    return true;
}

bool MIDISender::sendCC(int channel, int ccNumber, int velocity) {
    int _velocityClipped = velocity * 127;
    
    _velocityClipped =  _velocityClipped > 127 ? 127 : _velocityClipped;
    
    MidiMessage msg(juce::MidiMessage::controllerEvent (channel, ccNumber, _velocityClipped));
    
    ScopedPointer<MidiOutput> MIDI_OUT(MidiOutput::openDevice(0)); 

    MIDI_OUT->sendMessageNow(msg);
    
    return true;
}
