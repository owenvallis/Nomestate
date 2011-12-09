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
		
	void setMidiNoteEnabled(const String& midiDeviceName, int devicePos, bool input, bool enabled);
	void setMidiCCEnabled(const String& midiDeviceName, int devicePos, bool input, bool enabled);
	
	// int devicePos_:  which midi Device
	// bool input:		whether this is an input (true) of output (false) device
	bool isNoteEnabled(int devicePos_, bool input);
	bool isCcEnabled(int devicePos_, bool input);
	bool isMidiOutputEnabled(int devicePos_);

	//==========================================================================
	juce_UseDebuggingNewOperator
	
private:
	//==========================================================================
	Array<bool>					inputNote, inputCc;
	Array<bool>					outputNote, outputCc, outputEnabled;
	
	//==========================================================================
	// (prevent copy constructor and operator= being generated..)
	MidiIODeviceManager (const MidiIODeviceManager&);
	const MidiIODeviceManager& operator= (const MidiIODeviceManager&);
};


#endif  // __MIDIIODEVICEMANAGER_H_3A88AD76__
