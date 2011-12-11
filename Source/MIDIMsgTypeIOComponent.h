/*
  ==============================================================================

    MidiMsgTypeIOComponent.h
    Created: 3 Feb 2011 12:10:41pm
    Author:  owen vallis

  ==============================================================================
*/

#ifndef __MidiMsgTypeIOComponent_H_A183A3CE__
#define __MidiMsgTypeIOComponent_H_A183A3CE__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "MidiIODeviceManager.h"


class MidiMsgTypeIOComponent  : public Component,
public ButtonListener
{
public:
    //==============================================================================
    MidiMsgTypeIOComponent (MidiIODeviceManager& deviceManager_, 
                                            const String& midiDeviceName_, 
                                            bool input_);
    ~MidiMsgTypeIOComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);	
	
    //==============================================================================
    juce_UseDebuggingNewOperator
	
private:
	MidiIODeviceManager&			deviceManager;
	const String&					midiDeviceName;
    
	// is this a midi input or output device manager
	bool							input;
	
    //==============================================================================
    ScopedPointer<ToggleButton>		noteToggleButton;
    ScopedPointer<ToggleButton>		ccToggleButton;
    ScopedPointer<Label>			midiIODeviceName;
		
	//==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MidiMsgTypeIOComponent (const MidiMsgTypeIOComponent&);
    const MidiMsgTypeIOComponent& operator= (const MidiMsgTypeIOComponent&);
};



#endif  // __MidiMsgTypeIOComponent_H_A183A3CE__
