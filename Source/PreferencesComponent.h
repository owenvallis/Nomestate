/*
  ==============================================================================

    PreferencesComponent.h
    Created: 4 Dec 2011 11:08:43am
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __PREFERENCESCOMPONENT_H_E08C865C__
#define __PREFERENCESCOMPONENT_H_E08C865C__

#include "../JuceLibraryCode/JuceHeader.h"
#include "SignalCore.h"
#include "MidiIODeviceManager.h"


class PreferencesComponent :    public Component
{
    
    //==============================================================================
public:
	//===========================================================================
	PreferencesComponent(SignalCore& sCore, MidiIODeviceManager& deviceManager);
	~PreferencesComponent();
	
	//==========================================================================
	void paint (Graphics& g);
    void resized();	
	
	//==========================================================================
	juce_UseDebuggingNewOperator
	
private:
	//SignalCore*                             _sCore;
	
	//==========================================================================
	ScopedPointer<TabbedComponent>			prefTabs;
	
	//==========================================================================
	// (prevent copy constructor and operator= being generated..)
	PreferencesComponent (const PreferencesComponent&);
	const PreferencesComponent& operator= (const PreferencesComponent&);

};



#endif  // __PREFERENCESCOMPONENT_H_E08C865C__
