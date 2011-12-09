/*
  ==============================================================================

    AbletonStyleOSCComponent.cpp
    Created: 5 Dec 2011 12:16:23pm
    Author:  Owen Vallis

  ==============================================================================
*/

#include "AbletonStyleOSCComponent.h"

AbletonStyleOSCComponent::AbletonStyleOSCComponent() : setOSCPrefix("/box"),
                                                       setOSCPrefixLabel(String::empty, "Set OSC Prefix:"),
                                                       setConnectedDevice(String::empty, "Set Connected Device:")
{
    addAndMakeVisible (&setOSCPrefix);
    setOSCPrefix.addListener(this);
    setOSCPrefixLabel.setText("Set OSC Prefix", false);
    
    addAndMakeVisible (&setOSCPrefixLabel);
    setOSCPrefixLabel.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setOSCPrefixLabel.setJustificationType (Justification::centredLeft);
    setOSCPrefixLabel.setEditable (false, false, false);
    setOSCPrefixLabel.setColour (TextEditor::textColourId, Colours::black);
    setOSCPrefixLabel.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    
    // This should also happen in the callback from clicking the combobox
    for (int i = 0; i < PropertiesManager::getInstance()->connectedDevices.getNumChildren(); i++) {
        Value value(PropertiesManager::getInstance()->connectedDevices.getChild(i).getPropertyAsValue(Identifier("deviceName"), NULL));
        deviceNames.add(value.toString());
        connectedDevices.add(value.getValue());
        DBG(value.toString());
    }
  
    addAndMakeVisible( devices = new ChoicePropertyComponent (PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL), 
                                                              " ", 
                                                              deviceNames, 
                                                              connectedDevices));
    addAndMakeVisible (&setConnectedDevice);
    setConnectedDevice.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setConnectedDevice.setJustificationType (Justification::centredLeft);
    setConnectedDevice.setEditable (false, false, false);
    setConnectedDevice.setColour (TextEditor::textColourId, Colours::black);
    setConnectedDevice.setColour (TextEditor::backgroundColourId, Colour (0x0));
    //devices->setColour(ChoicePropertyComponent::backgroundColourId, Colours::black);

}

AbletonStyleOSCComponent::~AbletonStyleOSCComponent()
{
    
}

void AbletonStyleOSCComponent::paint (Graphics& g)
{
    g.setColour (Colour (0xffaab2b7));
    g.fillRect ((float) (proportionOfWidth (0.0000f)), 
				(float) (proportionOfHeight (0.0000f)), 
				(float) (proportionOfWidth (1.0000f)), 
				(float) (proportionOfHeight (1.0000f)));
	
	g.setColour (Colour (0xff66738c));
    g.drawRect ((proportionOfWidth (0.0000f)), 
				(proportionOfHeight (0.0000f)), 
				(proportionOfWidth (1.0000f)), 
				(proportionOfHeight (1.0000f)), 1);
	
	g.setColour (Colour (0xff66738c));
	g.fillRect ((float) (proportionOfWidth (0.0500f)), 
				(float) (proportionOfHeight (0.0500f)), 
				(float) (proportionOfWidth (0.9000f)), 
				18.0f);
}

void AbletonStyleOSCComponent::resized()
{
    
    const int h = 18;
	const int space = 6;
	const int dh = h + space;
	int y = proportionOfHeight (0.0500f) + 18 + space;
    
    ScopedPointer<Font> f(new Font(setOSCPrefixLabel.getFont ()));
    int width = f->getStringWidth(setOSCPrefixLabel.getText() );
    setOSCPrefixLabel.setBounds(proportionOfWidth (0.0500f),
                                 y,
                                 width + 10, h);
    
    setOSCPrefix.setBounds(proportionOfWidth (0.5800f) - 38, y, 100, 18.0f);
    
    f = new Font(setConnectedDevice.getFont ());
    width = f->getStringWidth(setConnectedDevice.getText() );
    setConnectedDevice.setBounds(proportionOfWidth (0.0500f),
                                y + dh,
                                width + 10, h);
    
    devices->setBounds(proportionOfWidth (0.5800f) - 38, y + dh, 100, 18.0f);
}

void AbletonStyleOSCComponent::textEditorReturnKeyPressed (TextEditor &editor)
{
    //send OSC to set /sys/prefix
    DBG("prefix changed...");
}