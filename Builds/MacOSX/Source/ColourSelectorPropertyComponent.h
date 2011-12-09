/*
  ==============================================================================

    ColourSelectorPropertyComponent.h
    Created: 14 Mar 2011 1:15:28am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef __COLOURSELECTORPROPERTYCOMPONENT_H_E092DF6E__
#define __COLOURSELECTORPROPERTYCOMPONENT_H_E092DF6E__

#include "../JuceLibraryCode/JuceHeader.h"

class ColourSelectorPropertyComponent :	public PropertyComponent, 
										public ChangeListener
{
	
public:
	ColourSelectorPropertyComponent				(const Value &v, const String& name);
	~ColourSelectorPropertyComponent			();
	void resized								();
	void refresh								();
	String getColourAsString					();
	void changeListenerCallback					(ChangeBroadcaster* source);
private:
	Value						val;
	ColourSelector				colourSelector;
		
};


#endif  // __COLOURSELECTORPROPERTYCOMPONENT_H_E092DF6E__
