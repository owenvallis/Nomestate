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


class MidiIOManagerComponent:  public Component	
{
	//==============================================================================
public:
	//===========================================================================
	MidiIOManagerComponent(MidiIODeviceManager& deviceManager);
	~MidiIOManagerComponent();
	
	//==========================================================================
	void paint (Graphics& g);
	void resized();	
	
	//==========================================================================
	juce_UseDebuggingNewOperator
	
private:
	
	//==========================================================================
	ScopedPointer<Label>                            midiPorts, note, cc;
	
	OwnedArray<MidiMsgTypeIOComponent>  midiInputs, midiOutputs;
	OwnedArray<Label>                               midiInputLabel, midiOutputLabel;
	StringArray                                     midiInputsList, midiOutputsList;
	
	//==========================================================================
	// (prevent copy constructor and operator= being generated..)
	MidiIOManagerComponent (const MidiIOManagerComponent&);
	const MidiIOManagerComponent& operator= (const MidiIOManagerComponent&);
};




#endif  // __MIDIIOMANAGERCOMPONENT_H_3F57D2E5__
