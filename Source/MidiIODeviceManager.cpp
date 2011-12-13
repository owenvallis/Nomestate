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
        if(!appProperties->getUserSettings()->containsKey(midiInputList[i] + "noteInputEnabled"))
        {
            appProperties->getUserSettings()->setValue(midiInputList[i] + "noteInputEnabled", var(false));
        } 
        else if (appProperties->getUserSettings()->getBoolValue(midiInputList[i] + "noteInputEnabled"))
        {
            setMidiInputEnabled(midiInputList[i], var(true));
        }
        
        if (!appProperties->getUserSettings()->containsKey(midiInputList[i] + "ccInputEnabled")) {
            appProperties->getUserSettings()->setValue(midiInputList[i] + "ccInputEnabled", var(false));
        } 
        else if (appProperties->getUserSettings()->getBoolValue(midiInputList[i] + "ccInputEnabled"))
        {
            setMidiInputEnabled(midiInputList[i], var(true));
        }
	}
	
	StringArray midiOutputList = MidiOutput::getDevices();
	for(int i = 0; i < midiOutputList.size(); i++)
	{
        if(!appProperties->getUserSettings()->containsKey(midiOutputList[i] + "noteOutputEnabled"))
        {
            appProperties->getUserSettings()->setValue(midiOutputList[i] + "noteOutputEnabled", var(false));
        } 
        else if (appProperties->getUserSettings()->getBoolValue(midiInputList[i] + "noteOutputEnabled"))
        {
            appProperties->getUserSettings()->setValue(midiOutputList[i] + "outputEnabled", var(true));
        }
        
        if (!appProperties->getUserSettings()->containsKey(midiOutputList[i] + "ccOutputEnabled")) {
            appProperties->getUserSettings()->setValue(midiOutputList[i] + "ccOutputEnabled", var(false));
        }
        else if (appProperties->getUserSettings()->getBoolValue(midiInputList[i] + "ccOutputEnabled"))
        {
            appProperties->getUserSettings()->setValue(midiOutputList[i] + "outputEnabled", var(true));
        }
        
        if (!appProperties->getUserSettings()->containsKey(midiOutputList[i] + "outputEnabled")) {
            appProperties->getUserSettings()->setValue(midiOutputList[i] + "outputEnabled", var(false));
        }
        else if (appProperties->getUserSettings()->getBoolValue(midiInputList[i] + "outputEnabled"))
        {
            appProperties->getUserSettings()->setValue(midiOutputList[i] + "outputEnabled", var(true));
        }
	}
    
    if(!appProperties->getUserSettings()->containsKey("midiInputChannel"))
    {
        int ch = 1;
        appProperties->getUserSettings()->setValue("midiInputChannel", var(ch));
    }
	
    if(!appProperties->getUserSettings()->containsKey("midiOutputChannel"))
    {
        int ch = 1;
        appProperties->getUserSettings()->setValue("midiOutputChannel", var(ch));
    }
    
    appProperties->saveIfNeeded();
}

MidiIODeviceManager::~MidiIODeviceManager()
{
}

void MidiIODeviceManager::setMidiNoteEnabled (const String& midiDeviceName, bool input, bool enabled)
{    
	if(input)
	{	
        appProperties->getUserSettings()->setValue(midiDeviceName + "noteInputEnabled", enabled);		
        
        // lets see if we need to turn the inputs on or off 
        if(enabled == true && isMidiInputEnabled(midiDeviceName) == false)
        {
            // we want to start listening to midi from this input
            setMidiInputEnabled(midiDeviceName, true);
        }
        else if(enabled == false 
                && isMidiInputEnabled(midiDeviceName) == true 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteInputEnabled") == false 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "ccInputEnabled") == false)
        {
            // no one is listening to this midi device, so lets turn it off
            setMidiInputEnabled(midiDeviceName, false);
        }
        
	}
	else if(!input)
	{
		appProperties->getUserSettings()->setValue(midiDeviceName + "noteOutputEnabled", var(enabled));
        
        // lets see if we need to turn the outputs on or off 
        if(enabled == true 
           && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteOutputEnabled")  == false)
        {
            // we want to start sending midi to this output
            appProperties->getUserSettings()->setValue(midiDeviceName + "outputEnabled", var(true));
        }
        else if(enabled == false 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "outputEnabled")  == true 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteOutputEnabled") == false 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "ccOutputEnabled") == false)
        {
            // no one wants to send to this midi device, so lets turn it off
            appProperties->getUserSettings()->setValue(midiDeviceName + "outputEnabled", var(false));
        }
        
        sendChangeMessage ();
        
        appProperties->saveIfNeeded();
	}
}

void MidiIODeviceManager::setMidiCCEnabled (const String& midiDeviceName, bool input, bool enabled)
{
	if(input)
	{	
        appProperties->getUserSettings()->setValue(midiDeviceName + "ccInputEnabled", enabled);		
        
        // lets see if we need to turn the inputs on or off 
        if(enabled == true && isMidiInputEnabled(midiDeviceName) == false)
        {
            // we want to start listening to midi from this input
            setMidiInputEnabled(midiDeviceName, true);
        }
        else if(enabled == false 
                && isMidiInputEnabled(midiDeviceName) == true 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteInputEnabled") == false 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "ccInputEnabled") == false)
        {
            // no one is listening to this midi device, so lets turn it off
            setMidiInputEnabled(midiDeviceName, false);
        }
	}
	else if(!input)
	{
		
        appProperties->getUserSettings()->setValue(midiDeviceName + "ccOutputEnabled", enabled);	
        
        // lets see if we need to turn the outputs on or off 
        if(enabled == true 
           && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteOutputEnabled")  == false)
        {
            // we want to start sending midi to this output
            appProperties->getUserSettings()->setValue(midiDeviceName + "outputEnabled", true);
        }
        else if(enabled == false 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "outputEnabled")  == true 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteOutputEnabled") == false 
                && appProperties->getUserSettings()->getBoolValue(midiDeviceName + "ccOutputEnabled") == false)
        {
            // no one wants to send to this midi device, so lets turn it off
            appProperties->getUserSettings()->setValue(midiDeviceName + "outputEnabled", true);
        }
        
        sendChangeMessage ();
	}
    
    appProperties->saveIfNeeded();
}

bool MidiIODeviceManager::isNoteEnabled (String midiDeviceName, bool input)
{
	if(input)
		return appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteInputEnabled");
	
	else if(!input)
		return appProperties->getUserSettings()->getBoolValue(midiDeviceName + "noteOutputEnabled");
	
	return false;
}

bool MidiIODeviceManager::isCcEnabled (String midiDeviceName, bool input)
{
	if(input)
		return appProperties->getUserSettings()->getBoolValue(midiDeviceName + "ccInputEnabled");
	
	else if(!input)
		return appProperties->getUserSettings()->getBoolValue(midiDeviceName + "ccOutputEnabled");
	
	return false;
}

bool MidiIODeviceManager::isMidiOutputEnabled (String midiDeviceName)
{	
	return appProperties->getUserSettings()->getBoolValue(midiDeviceName + "OutputEnabled");
}
