/*
 *  CustomLookAndFeel.cpp
 *  Nuance
 *
 *  Created by Jordan Hochenbaum on 2/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel() 
{
	//buttons
	this->setColour(TextButton::buttonColourId, Colours::grey);
		
	//other
	this->setColour(ComboBox::buttonColourId, Colour(100,100,100));
	this->setColour(ComboBox::backgroundColourId, Colours::white);
	this->setColour(TextEditor::outlineColourId, Colours::lightgrey);
	this->setColour(TextEditor::focusedOutlineColourId, Colours::transparentBlack);
	this->setColour(ColourSelector::backgroundColourId, Colour(100,100,100));
}

CustomLookAndFeel::~CustomLookAndFeel()
{

}