/*
  ==============================================================================

    MidiIODeviceManager.cpp
    Created: 3 Feb 2011 5:07:06pm
    Author:  owen vallis

  ==============================================================================
*/

#include "MidiIODeviceManager.h"


MidiIODeviceManager::MidiIODeviceManager() : _midiInputEnabled("midiInputEnabled"),
                                             _midiOutputEnabled("midiOutputEnabled"),
                                             noteInputEnabled("noteInputEnabled"),
                                             ccInputEnabled("ccInputEnabled"),
                                             noteOutputEnabled("noteOutputEnabled"),
                                             ccOutputEnabled("ccOutputEnabled"),
                                             outputEnabled("outputEnabled")
{
	StringArray midiInputList = MidiInput::getDevices();
	for(int i = 0; i < midiInputList.size(); i++)
	{
        _midiInputEnabled.addChild(ValueTree(Identifier(midiInputList[i].removeCharacters ("\"#@,;:<>*^|?\\/() "))), -1, NULL);
        _midiInputEnabled.getChild(_midiInputEnabled.getNumChildren()-1).setProperty(noteInputEnabled, false, NULL);
        _midiInputEnabled.getChild(_midiInputEnabled.getNumChildren()-1).setProperty(ccInputEnabled, false, NULL);
	}
	
	StringArray midiOutputList = MidiOutput::getDevices();
	for(int i = 0; i < midiOutputList.size(); i++)
	{
        _midiOutputEnabled.addChild(ValueTree(Identifier(midiInputList[i].removeCharacters ("\"#@,;:<>*^|?\\/() "))), -1, NULL);
        _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(noteOutputEnabled, false, NULL);
        _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(ccOutputEnabled, false, NULL);
        _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(outputEnabled, false, NULL);
	}	
}

MidiIODeviceManager::~MidiIODeviceManager()
{
}

void MidiIODeviceManager::setMidiNoteEnabled (const String& midiDeviceName, bool input, bool enabled)
{
    String strippedMidiDeviceName = midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() ");
    
	if(input)
	{	
        // lets update our enabled midi input lists
		if(_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).isValid() )
		{
			_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(noteInputEnabled, enabled, NULL);
		}
		else
		{
			DBG("adding new midi input to our list of available inputs");
            
            _midiInputEnabled.addChild(ValueTree(Identifier(strippedMidiDeviceName)), -1, NULL);
            _midiInputEnabled.getChild(_midiInputEnabled.getNumChildren()-1).setProperty(noteInputEnabled, enabled, NULL);
            _midiInputEnabled.getChild(_midiInputEnabled.getNumChildren()-1).setProperty(ccInputEnabled, false, NULL);
		}
        
        // lets see if we need to turn the inputs on or off 
        if(enabled == true && isMidiInputEnabled(midiDeviceName) == false)
        {
            // we want to start listening to midi from this input
            setMidiInputEnabled(midiDeviceName, true);
        }
        else if(enabled == false 
                && isMidiInputEnabled(midiDeviceName) == true 
                && (bool)_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(noteInputEnabled, NULL).getValue() == false 
                && (bool)_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(ccInputEnabled, NULL).getValue() == false)
        {
            // no one is listening to this midi device, so lets turn it off
            setMidiInputEnabled(midiDeviceName, false);
        }
        
	}
	else if(!input)
	{
		
		if(_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).isValid() )
		{
			_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(noteOutputEnabled, enabled, NULL);
		}
		else
		{
			DBG("adding new midi input to our list of available outputs");
            
            _midiOutputEnabled.addChild(ValueTree(Identifier(strippedMidiDeviceName)), -1, NULL);
            _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(noteOutputEnabled, enabled, NULL);
            _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(ccOutputEnabled, false, NULL);
            _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(outputEnabled, false, NULL);
		}	
        
        // lets see if we need to turn the outputs on or off 
        if(enabled == true 
           && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(outputEnabled, NULL).getValue()  == false)
        {
            // we want to start sending midi to this output
            _midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(outputEnabled, true, NULL);
        }
        else if(enabled == false 
                && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(outputEnabled, NULL).getValue()  == true 
                && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(noteOutputEnabled, NULL).getValue() == false 
                && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(ccOutputEnabled, NULL).getValue() == false)
        {
            // no one wants to send to this midi device, so lets turn it off
            _midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(outputEnabled, false, NULL);
        }
        
        sendChangeMessage ();
	}
}

void MidiIODeviceManager::setMidiCCEnabled (const String& midiDeviceName, bool input, bool enabled)
{
    String strippedMidiDeviceName = midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() ");

	if(input)
	{	
        // lets update our enabled midi input lists
		if(_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).isValid() )
		{
			_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(ccInputEnabled, enabled, NULL);
		}
		else
		{
			DBG("adding new midi input to our list of available inputs");
            
            _midiInputEnabled.addChild(ValueTree(Identifier(strippedMidiDeviceName)), -1, NULL);
            _midiInputEnabled.getChild(_midiInputEnabled.getNumChildren()-1).setProperty(noteInputEnabled, false, NULL);
            _midiInputEnabled.getChild(_midiInputEnabled.getNumChildren()-1).setProperty(ccInputEnabled, enabled, NULL);
		}
        
        // lets see if we need to turn the inputs on or off 
        if(enabled == true && isMidiInputEnabled(midiDeviceName) == false)
        {
            // we want to start listening to midi from this input
            setMidiInputEnabled(midiDeviceName, true);
        }
        else if(enabled == false 
                && isMidiInputEnabled(midiDeviceName) == true 
                && (bool)_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(noteInputEnabled, NULL).getValue() == false 
                && (bool)_midiInputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(ccInputEnabled, NULL).getValue() == false)
        {
            // no one is listening to this midi device, so lets turn it off
            setMidiInputEnabled(midiDeviceName, false);
        }
	}
	else if(!input)
	{
		
		if(_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).isValid() )
		{
			_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(ccOutputEnabled, enabled, NULL);
		}
		else
		{
			DBG("adding new midi input to our list of available outputs");
            
            _midiOutputEnabled.addChild(ValueTree(Identifier(strippedMidiDeviceName)), -1, NULL);
            _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(noteOutputEnabled, false, NULL);
            _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(ccOutputEnabled, enabled, NULL);
            _midiOutputEnabled.getChild(_midiOutputEnabled.getNumChildren()-1).setProperty(outputEnabled, false, NULL);
		}	
        
        // lets see if we need to turn the outputs on or off 
        if(enabled == true 
           && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(outputEnabled, NULL).getValue()  == false)
        {
            // we want to start sending midi to this output
            _midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(outputEnabled, true, NULL);
        }
        else if(enabled == false 
                && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(outputEnabled, NULL).getValue()  == true 
                && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(noteOutputEnabled, NULL).getValue() == false 
                && (bool)_midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).getPropertyAsValue(ccOutputEnabled, NULL).getValue() == false)
        {
            // no one wants to send to this midi device, so lets turn it off
            _midiOutputEnabled.getChildWithName(Identifier(strippedMidiDeviceName)).setProperty(outputEnabled, false, NULL);
        }
        
        sendChangeMessage ();
	}}

bool MidiIODeviceManager::isNoteEnabled (String midiDeviceName, bool input)
{
	if(input)
		return _midiInputEnabled.getChildWithName(Identifier(midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() "))).getPropertyAsValue(noteInputEnabled, NULL).getValue();
	
	else if(!input)
		return _midiOutputEnabled.getChildWithName(Identifier(midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() "))).getPropertyAsValue(noteOutputEnabled, NULL).getValue();
	
	return false;
}

bool MidiIODeviceManager::isCcEnabled (String midiDeviceName, bool input)
{
	if(input)
		return _midiInputEnabled.getChildWithName(Identifier(midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() "))).getPropertyAsValue(ccInputEnabled, NULL).getValue();
	
	else if(!input)
		return _midiOutputEnabled.getChildWithName(Identifier(midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() "))).getPropertyAsValue(ccOutputEnabled, NULL).getValue();
	
	return false;
}

bool MidiIODeviceManager::isMidiOutputEnabled (String midiDeviceName)
{	
	return _midiOutputEnabled.getChildWithName(Identifier(midiDeviceName.removeCharacters ("\"#@,;:<>*^|?\\/() "))).getPropertyAsValue(outputEnabled, NULL).getValue();
}

//************************ Saving state 