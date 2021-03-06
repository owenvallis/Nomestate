/*
  ==============================================================================

    MIDISender.h
    Created: 10 Oct 2011 10:02:54pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __MIDISENDER_H_20023A57__
#define __MIDISENDER_H_20023A57__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Signal.h"
#include "MidiIODeviceManager.h"

extern ApplicationProperties* appProperties;

class MIDISender {
    
public:
    
    MIDISender(MidiIODeviceManager &pMidiIODeviceManager); 
    ~MIDISender();
    
    
    void handleSignal(Signal s); 
    
    
private:
    
    MidiIODeviceManager* _pDeviceManager;
    
    bool sendNoteOn(int channel, int noteNumber, uint8 velocity); 
    bool sendNoteOff(int channel, int noteNumber); 
    bool sendCC(int channel, int ccNumber, int velocity);

};

#endif  // __MIDISENDER_H_20023A57__
