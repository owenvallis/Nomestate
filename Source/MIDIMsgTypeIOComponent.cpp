/*
  ==============================================================================

    MidiMsgTypeIOComponent.cpp
    Created: 3 Feb 2011 12:10:41pm
    Author:  owen vallis

  ==============================================================================
*/

#include "MidiMsgTypeIOComponent.h"

//==============================================================================
MidiMsgTypeIOComponent::MidiMsgTypeIOComponent (MidiIODeviceManager& deviceManager_, 
														  const String& midiDeviceName_, 
                                                        bool input_)
	: Component ("MidiMsgTypeIOComponent"),
	  deviceManager(deviceManager_),
	  midiDeviceName(midiDeviceName_),
	  input(input_)
{
    addAndMakeVisible (noteToggleButton = new ToggleButton ("note"));
	noteToggleButton->setToggleState (deviceManager.isNoteEnabled(midiDeviceName_, input), false);
    noteToggleButton->setButtonText (String::empty);
    noteToggleButton->addListener (this);
	
    addAndMakeVisible (ccToggleButton = new ToggleButton ("cc"));
	ccToggleButton->setToggleState (deviceManager.isCcEnabled(midiDeviceName_, input), false);
    ccToggleButton->setButtonText (String::empty);
    ccToggleButton->addListener (this);
	
    addAndMakeVisible (midiIODeviceName = new Label ("midiIODeviceName", midiDeviceName));
    midiIODeviceName->setFont (Font (Font::getDefaultSansSerifFontName (), 11.0000f, Font::bold));
    midiIODeviceName->setJustificationType (Justification::centredLeft);
    midiIODeviceName->setEditable (false, false, false);
    midiIODeviceName->setColour (TextEditor::textColourId, Colours::black);
    midiIODeviceName->setColour (TextEditor::backgroundColourId, Colour (0x0));
	
    setSize (500, 24);

}

MidiMsgTypeIOComponent::~MidiMsgTypeIOComponent()
{
}

//==============================================================================
void MidiMsgTypeIOComponent::paint (Graphics& g)
{	
}

void MidiMsgTypeIOComponent::resized()
{
    noteToggleButton->setBounds (proportionOfWidth (0.5800f) - 38, 0, 38, getHeight());
    ccToggleButton->setBounds (proportionOfWidth (0.8200f) - 38, 0, 38, getHeight());
	
	ScopedPointer<Font> f(new Font(midiIODeviceName->getFont ()) );
	int width = f->getStringWidth(midiIODeviceName->getText() );
    midiIODeviceName->setBounds (proportionOfWidth (0.0000f), 0, width + 10, getHeight());
}

void MidiMsgTypeIOComponent::buttonClicked (Button* buttonThatWasClicked)
{
	
    if (buttonThatWasClicked == noteToggleButton)
    {
		deviceManager.setMidiNoteEnabled(midiDeviceName, input, buttonThatWasClicked->getToggleState());
    }
    else if (buttonThatWasClicked == ccToggleButton)
    {
		deviceManager.setMidiCCEnabled(midiDeviceName, input, buttonThatWasClicked->getToggleState());

    }
}