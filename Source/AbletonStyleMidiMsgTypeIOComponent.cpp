/*
  ==============================================================================

    AbletonStyleMidiMsgTypeIOComponent.cpp
    Created: 3 Feb 2011 12:10:41pm
    Author:  owen vallis

  ==============================================================================
*/

#include "AbletonStyleMidiMsgTypeIOComponent.h"

//==============================================================================
AbletonStyleMidiMsgTypeIOComponent::AbletonStyleMidiMsgTypeIOComponent (MidiIODeviceManager& deviceManager_, 
														  const String& midiDeviceName_, 
														  int deviceNum_, bool input_)
	: Component ("AbletonStyleMidiMsgTypeIOComponent"),
	  deviceManager(deviceManager_),
	  midiDeviceName(midiDeviceName_),
	  deviceNum(deviceNum_),
	  input(input_)
{
    addAndMakeVisible (noteToggleButton = new ToggleButton ("note"));
	noteToggleButton->setToggleState (deviceManager.isNoteEnabled(deviceNum, input), false);
    noteToggleButton->setButtonText (String::empty);
    noteToggleButton->addListener (this);
	
    addAndMakeVisible (ccToggleButton = new ToggleButton ("cc"));
	ccToggleButton->setToggleState (deviceManager.isCcEnabled(deviceNum, input), false);
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

AbletonStyleMidiMsgTypeIOComponent::~AbletonStyleMidiMsgTypeIOComponent()
{
}

//==============================================================================
void AbletonStyleMidiMsgTypeIOComponent::paint (Graphics& g)
{	
}

void AbletonStyleMidiMsgTypeIOComponent::resized()
{
    noteToggleButton->setBounds (proportionOfWidth (0.5800f) - 38, 0, 38, getHeight());
    ccToggleButton->setBounds (proportionOfWidth (0.8200f) - 38, 0, 38, getHeight());
	
	ScopedPointer<Font> f(new Font(midiIODeviceName->getFont ()) );
	int width = f->getStringWidth(midiIODeviceName->getText() );
    midiIODeviceName->setBounds (proportionOfWidth (0.0000f), 0, width + 10, getHeight());
}

void AbletonStyleMidiMsgTypeIOComponent::buttonClicked (Button* buttonThatWasClicked)
{
	
    if (buttonThatWasClicked == noteToggleButton)
    {
		deviceManager.setMidiNoteEnabled(midiDeviceName, deviceNum, input, buttonThatWasClicked->getToggleState());
    }
    else if (buttonThatWasClicked == ccToggleButton)
    {
		deviceManager.setMidiCCEnabled(midiDeviceName, deviceNum, input, buttonThatWasClicked->getToggleState());

    }

}