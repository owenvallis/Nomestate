/*
  ==============================================================================

    ColourSelectorPropertyComponent.cpp
    Created: 14 Mar 2011 1:15:28am
    Author:  Jordan Hochenbaum & Owen Vallis

  ==============================================================================
*/

#include "ColourSelectorPropertyComponent.h"

ColourSelectorPropertyComponent::ColourSelectorPropertyComponent(const Value &v, const String& name) : PropertyComponent(name), val(v), colourSelector(ColourSelector::showColourspace)
{
	addAndMakeVisible(&colourSelector);
	setPreferredHeight(200);
	colourSelector.addChangeListener(this);
}

ColourSelectorPropertyComponent::~ColourSelectorPropertyComponent()
{
}

void ColourSelectorPropertyComponent::changeListenerCallback (ChangeBroadcaster* source)
{
	val = colourSelector.getCurrentColour().toString();
}


void ColourSelectorPropertyComponent::resized()
{
	colourSelector.setBounds(0, 0, getWidth(), getHeight());
}

void ColourSelectorPropertyComponent::refresh()
{
	colourSelector.setCurrentColour(Colour::fromString (val.toString()));
}

String ColourSelectorPropertyComponent::getColourAsString()
{
	return colourSelector.getCurrentColour().toString();
}