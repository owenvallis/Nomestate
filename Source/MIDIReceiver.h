/*
  ==============================================================================

    MIDIReceiver.h
    Created: 10 Oct 2011 10:02:49pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __MIDIRECEIVER_H_F971C991__
#define __MIDIRECEIVER_H_F971C991__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MessageCenter.h"
#include "Signal.h"
#include "MidiIODeviceManager.h"

extern ApplicationProperties* appProperties;

class MIDIReceiver : public MidiInputCallback

{
public:
    MIDIReceiver(MessageCenter &center, MidiIODeviceManager &MidiDeviceManager);
    ~MIDIReceiver(); 
    
    void handleIncomingMidiMessage	(MidiInput *source, const MidiMessage &message);
    
private:
    
    MessageCenter *_mCenter;
    
    MidiIODeviceManager *_MidiDeviceManager;
};



#endif  // __MIDIRECEIVER_H_F971C991__
