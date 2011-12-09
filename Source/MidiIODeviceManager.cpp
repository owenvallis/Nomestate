/*
  ==============================================================================

    MidiIODeviceManager.cpp
    Created: 3 Feb 2011 5:07:06pm
    Author:  owen vallis

  ==============================================================================
*/

#include "MidiIODeviceManager.h"

MidiIODeviceManager::MidiIODeviceManager()
{
	StringArray midiInputList = MidiInput::getDevices();
	for(int i = 0; i < midiInputList.size(); i++)
	{
		inputNote.add(false);
		inputCc.add(false);
	}
	
	StringArray midiOutputList = MidiOutput::getDevices();
	for(int i = 0; i < midiOutputList.size(); i++)
	{
		outputNote.add(false);
		outputCc.add(false);
		outputEnabled.add(false);
	}	
}

MidiIODeviceManager::~MidiIODeviceManager()
{
}

void MidiIODeviceManager::setMidiNoteEnabled (const String& midiDeviceName, int devicePos, bool input, bool enabled)
{
	if(input)
	{	
		if(devicePos < inputNote.size() )
		{
			inputNote.set(devicePos, enabled);
			if(enabled == true && isMidiInputEnabled(midiDeviceName) == false)
			{
				setMidiInputEnabled(midiDeviceName, enabled);
			}
			else if(enabled == false && isMidiInputEnabled(midiDeviceName) == true && 
					inputNote[devicePos] == false && inputCc[devicePos] == false)
			{
				setMidiInputEnabled(midiDeviceName, enabled);
			}
		}
		else
		{
			DBG("device outside the range of inputNote");
		}
	}
	else
	{
		
		if(devicePos < outputNote.size() )
		{
			outputNote.set(devicePos, enabled);
			if(enabled == true && outputEnabled[devicePos] == false)
			{
				outputEnabled.set(devicePos,enabled);
			}
			else if(enabled == false && outputEnabled[devicePos] == true && 
					outputNote[devicePos] == false && outputCc[devicePos] == false)
			{
				outputEnabled.set(devicePos, enabled);
			}
			
			sendChangeMessage ();
		}
		else
		{
			DBG("device outside the range of outputNote");
		}		
	}
}

void MidiIODeviceManager::setMidiCCEnabled (const String& midiDeviceName, int devicePos, bool input, bool enabled)
{
	if(input)
	{	
		if(devicePos < inputCc.size() )
		{
			inputCc.set(devicePos, enabled);
			if(enabled == true && isMidiInputEnabled(midiDeviceName) == false)
			{
				setMidiInputEnabled(midiDeviceName, enabled);
			}
			else if(enabled == false && isMidiInputEnabled(midiDeviceName) == true && 
					inputNote[devicePos] == false && inputCc[devicePos] == false)
			{
				setMidiInputEnabled(midiDeviceName, enabled);
			}
		}
		else
		{
			DBG("device outside the range of inputNote");
		}
	}
	else
	{
		
		if(devicePos < outputCc.size() )
		{
			outputCc.set(devicePos, enabled);
			if(enabled == true && outputEnabled[devicePos] == false)
			{
				outputEnabled.set(devicePos,enabled);
			}
			else if(enabled == false && outputEnabled[devicePos] == true && 
					outputNote[devicePos] == false && outputCc[devicePos] == false)
			{
				outputEnabled.set(devicePos, enabled);
			}
			
			sendChangeMessage ();
		}
		else
		{
			DBG("device outside the range of outputNote");
		}		
	}
}

bool MidiIODeviceManager::isNoteEnabled (int devicePos_, bool input)
{
	if(input)
		return inputNote[devicePos_];
	
	else if(!input)
		return outputNote[devicePos_];
	
	return false;
}

bool MidiIODeviceManager::isCcEnabled (int devicePos_, bool input)
{
	if(input)
		return inputCc[devicePos_];
	
	else if(!input)
		return outputCc[devicePos_];
	
	return false;
}

bool MidiIODeviceManager::isMidiOutputEnabled (int devicePos_)
{	
	return outputEnabled[devicePos_];
}