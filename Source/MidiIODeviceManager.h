/*
  ==============================================================================

    MidiIODeviceManager.h
    Created: 3 Feb 2011 5:07:06pm
    Author:  owen vallis

  ==============================================================================
*/

#ifndef __MIDIIODEVICEMANAGER_H_3A88AD76__
#define __MIDIIODEVICEMANAGER_H_3A88AD76__

#include "../JuceLibraryCode/JuceHeader.h"


class MidiIODeviceManager:  public AudioDeviceManager
{
public:
	//===========================================================================
	MidiIODeviceManager();
	~MidiIODeviceManager();
		
	void setMidiNoteEnabled(const String& midiDeviceName, bool input, bool enabled);
	void setMidiCCEnabled(const String& midiDeviceName, bool input, bool enabled);
	
	// int devicePos_:  which midi Device
	// bool input:		whether this is an input (true) of output (false) device
	bool isNoteEnabled(String midiDeviceName, bool input);
	bool isCcEnabled(String midiDeviceName, bool input);
	bool isMidiOutputEnabled(String midiDeviceName);
    
    //==========================================================================
    ValueTree         _midiInputEnabled;
    ValueTree         _midiOutputEnabled;

	//==========================================================================
	juce_UseDebuggingNewOperator
	
private:
    //==========================================================================
    // midi input
    const Identifier  noteInputEnabled;
    const Identifier  ccInputEnabled;
    
    // midi output
    const Identifier  noteOutputEnabled;
    const Identifier  ccOutputEnabled;
    const Identifier  outputEnabled;
	
	//==========================================================================
	// (prevent copy constructor and operator= being generated..)
	MidiIODeviceManager (const MidiIODeviceManager&);
	const MidiIODeviceManager& operator= (const MidiIODeviceManager&);
};


#endif  // __MIDIIODEVICEMANAGER_H_3A88AD76__
