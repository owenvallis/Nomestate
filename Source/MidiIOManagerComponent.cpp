/*
  ==============================================================================

    MidiIOManagerComponent.cpp
    Created: 3 Feb 2011 2:32:39pm
    Author:  owen vallis

  ==============================================================================
*/

#include "MidiIOManagerComponent.h"


//==============================================================================
MidiIOManagerComponent::MidiIOManagerComponent (MidiIODeviceManager& deviceManager) 
{	
	midiInputsList = MidiInput::getDevices();
	midiOutputsList = MidiOutput::getDevices();
	
	for(int i = 0; i < midiInputsList.size(); i++)
	{
		midiInputs.add(new MidiMsgTypeIOComponent(deviceManager, midiInputsList[i], i, true) );
		addAndMakeVisible(midiInputs[i]);
	}
	
	for(int i = 0; i < midiOutputsList.size(); i++)
	{
		midiOutputs.add(new MidiMsgTypeIOComponent(deviceManager, midiOutputsList[i], i, false) );
		addAndMakeVisible(midiOutputs[i]);
	}
	
	addAndMakeVisible(midiPorts = new Label ("midiPorts", "MIDI Ports"));
    midiPorts->setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    midiPorts->setJustificationType (Justification::centredLeft);
    midiPorts->setEditable (false, false, false);
    midiPorts->setColour (TextEditor::textColourId, Colours::lightgrey);
	
	addAndMakeVisible(note = new Label ("note", "Note"));
    note->setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    note->setJustificationType (Justification::centredLeft);
    note->setEditable (false, false, false);
    note->setColour (TextEditor::textColourId, Colours::lightgrey);
	
	addAndMakeVisible(cc = new Label ("cc", "CC"));
    cc->setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    cc->setJustificationType (Justification::centredLeft);
    cc->setEditable (false, false, false);
    cc->setColour (TextEditor::textColourId, Colours::lightgrey );
}

MidiIOManagerComponent::~MidiIOManagerComponent()
{
	
}

//==============================================================================
void MidiIOManagerComponent::paint (Graphics& g)
{
    g.setColour (Colour (81,81,81));
    g.fillRect ((float) (proportionOfWidth (0.0000f)), 
				(float) (proportionOfHeight (0.0000f)), 
				(float) (proportionOfWidth (1.0000f)), 
				(float) (proportionOfHeight (1.0000f)));
	
	g.setColour (Colour (25,25,25));
	g.fillRect ((float) (proportionOfWidth (0.0500f)), 
				(float) (proportionOfHeight (0.0500f)), 
				(float) (proportionOfWidth (0.9000f)), 
				18.0f);
}

void MidiIOManagerComponent::resized()
{
    
	// labels
	ScopedPointer<Font> f(new Font(midiPorts->getFont ()) );
	int width = f->getStringWidth(midiPorts->getText() );
	
	midiPorts->setBounds(proportionOfWidth (0.2500f), 
						 proportionOfHeight (0.0500f), 
						 width + 10, 18.0f);
	
	f = new Font(note->getFont ());
	width = f->getStringWidth(note->getText() );
	note->setBounds(proportionOfWidth (0.6300f), 
						 proportionOfHeight (0.0500f), 
						 width + 10, 18.0f);
	
	f = new Font(cc->getFont ());
	width = f->getStringWidth(cc->getText() );
	cc->setBounds(proportionOfWidth (0.8550f), 
						 proportionOfHeight (0.0500f), 
						 width + 10, 18.0f);
	
	// inputs
	const int h = 18;
	const int space = 6;
	const int dh = h + space;
	int y = proportionOfHeight (0.0500f) + 18 + space;
	
	midiInputLabel.clear();
	
	for(int i = 0; i < midiInputsList.size(); i++)
	{
		midiInputLabel.add(new Label(String::empty, "Input: ") );
		addAndMakeVisible(midiInputLabel[i]);
		midiInputLabel[i]->setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
		midiInputLabel[i]->setJustificationType (Justification::centredLeft);
		midiInputLabel[i]->setEditable (false, false, false);
		midiInputLabel[i]->setColour (TextEditor::textColourId, Colour(25,25,25).contrasting(1.0f));
		midiInputLabel[i]->setColour (TextEditor::backgroundColourId, Colour (0x0));
		
		f = new Font(midiInputLabel[i]->getFont ());
		width = f->getStringWidth(midiInputLabel[i]->getText() );
		midiInputLabel[i]->setBounds(proportionOfWidth (0.0500f),
									  y + (dh * i),
									  width + 10, h);
		
		midiInputs[i]->setBounds(proportionOfWidth (0.2000f),
								 y + (dh * i),
								 proportionOfWidth (0.9000f),
								 h);
	}
	
	//outputs
	y = y + (dh * midiInputsList.size()-1);
	
	midiOutputLabel.clear();
	
	for(int i = 0; i < midiOutputsList.size(); i++)
	{
		midiOutputLabel.add(new Label(String::empty, "Output: ") );
		addAndMakeVisible(midiOutputLabel[i]);
		midiOutputLabel[i]->setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
		midiOutputLabel[i]->setJustificationType (Justification::centredLeft);
		midiOutputLabel[i]->setEditable (false, false, false);
		midiOutputLabel[i]->setColour (TextEditor::textColourId, Colour(25,25,25).contrasting(1.0f));
		midiOutputLabel[i]->setColour (TextEditor::backgroundColourId, Colour (0x0));
		
		f = new Font(midiOutputLabel[i]->getFont ());
		width = f->getStringWidth(midiOutputLabel[i]->getText() );
		midiOutputLabel[i]->setBounds(proportionOfWidth (0.0500f),
									  y + (dh * i),
									  width + 10, h);
		
		midiOutputs[i]->setBounds(proportionOfWidth (0.2000f),
								 y + (dh * i),
								 proportionOfWidth (0.9000f),
								 h);
	}    
}