/*
  ==============================================================================

    MidiIOManagerComponent.h
    Created: 3 Feb 2011 2:32:39pm
    Author:  owen vallis

  ==============================================================================
*/

#ifndef __MIDIIOMANAGERCOMPONENT_H_3F57D2E5__
#define __MIDIIOMANAGERCOMPONENT_H_3F57D2E5__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiMsgTypeIOComponent.h"
#include "MidiIODeviceManager.h"

extern ApplicationProperties* appProperties;

class MidiIOManagerComponent:  public Component,
                               public ComboBox::Listener
{
	//==============================================================================
public:
	//===========================================================================
	MidiIOManagerComponent(MidiIODeviceManager& deviceManager);
	~MidiIOManagerComponent();
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
	
	//==========================================================================
	void paint (Graphics& g);
	void resized();	
	
	//==========================================================================
	juce_UseDebuggingNewOperator
	
private:
	
	//==========================================================================
	ScopedPointer<Label>                            midiPorts, note, cc;
	
	OwnedArray<MidiMsgTypeIOComponent>              midiInputs, midiOutputs;
	OwnedArray<Label>                               midiInputLabel, midiOutputLabel;
	StringArray                                     midiInputsList, midiOutputsList;
    
    ComboBox                                        midiInputChannel, midiOutputChannel;
    Label                                           midiInputChannelLabel, midiOutputChannelLabel;
	
	//==========================================================================
	// (prevent copy constructor and operator= being generated..)
	MidiIOManagerComponent (const MidiIOManagerComponent&);
	const MidiIOManagerComponent& operator= (const MidiIOManagerComponent&);
};




#endif  // __MIDIIOMANAGERCOMPONENT_H_3F57D2E5__
