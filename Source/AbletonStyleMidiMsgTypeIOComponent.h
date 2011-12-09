/*
  ==============================================================================

    AbletonStyleMidiMsgTypeIOComponent.h
    Created: 3 Feb 2011 12:10:41pm
    Author:  owen vallis

  ==============================================================================
*/

#ifndef __AbletonStyleMidiMsgTypeIOComponent_H_A183A3CE__
#define __AbletonStyleMidiMsgTypeIOComponent_H_A183A3CE__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "MidiIODeviceManager.h"


class AbletonStyleMidiMsgTypeIOComponent  : public Component,
public ButtonListener
{
public:
    //==============================================================================
    AbletonStyleMidiMsgTypeIOComponent (MidiIODeviceManager& deviceManager_, 
                                            const String& midiDeviceName_, 
                                            int deviceNum_, bool input_);
    ~AbletonStyleMidiMsgTypeIOComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);	
	
    //==============================================================================
    juce_UseDebuggingNewOperator
	
private:
	MidiIODeviceManager&			deviceManager;
	const String&					midiDeviceName;
	int								deviceNum;
	// is this a midi input or output device manager
	bool							input;
	
    //==============================================================================
    ScopedPointer<ToggleButton>		noteToggleButton;
    ScopedPointer<ToggleButton>		ccToggleButton;
    ScopedPointer<Label>			midiIODeviceName;
		
	//==============================================================================
    // (prevent copy constructor and operator= being generated..)
    AbletonStyleMidiMsgTypeIOComponent (const AbletonStyleMidiMsgTypeIOComponent&);
    const AbletonStyleMidiMsgTypeIOComponent& operator= (const AbletonStyleMidiMsgTypeIOComponent&);
};



#endif  // __AbletonStyleMidiMsgTypeIOComponent_H_A183A3CE__
