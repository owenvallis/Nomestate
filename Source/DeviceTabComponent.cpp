/*
  ==============================================================================

    DeviceTabComponent.cpp
    Created: 5 Dec 2011 12:16:23pm
    Author:  Owen Vallis

  ==============================================================================
*/

#include "DeviceTabComponent.h"

DeviceTabComponent::DeviceTabComponent(SignalCore& sCore) : setConnectedDevice(String::empty, "Set Connected Device:"),
                                                       setListenPort("8000"),
                                                       setListenPortLabel(String::empty, "Listen Port:"),
                                                       setHostPort("8080"),
                                                       setHostPortLabel(String::empty, "Host Port:")
{
    _sCore = &sCore;

    
    addAndMakeVisible(&setListenPort);
    setListenPort.addListener(this);
    
    addAndMakeVisible(&setListenPortLabel);
    setListenPortLabel.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setListenPortLabel.setJustificationType (Justification::centredLeft);
    setListenPortLabel.setEditable (false, false, false);
    setListenPortLabel.setColour (TextEditor::textColourId, Colours::black);
    setListenPortLabel.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    addAndMakeVisible(&setHostPort);
    setHostPort.addListener(this);
    
    addAndMakeVisible(&setHostPortLabel);
    setHostPortLabel.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setHostPortLabel.setJustificationType (Justification::centredLeft);
    setHostPortLabel.setEditable (false, false, false);
    setHostPortLabel.setColour (TextEditor::textColourId, Colours::black);
    setHostPortLabel.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    
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

}

DeviceTabComponent::~DeviceTabComponent()
{
    
}

void DeviceTabComponent::paint (Graphics& g)
{
    g.setColour (Colour (81,81,81));
    g.fillRect ((float) (proportionOfWidth (0.0000f)), 
				(float) (proportionOfHeight (0.0000f)), 
				(float) (proportionOfWidth (1.0000f)), 
				(float) (proportionOfHeight (1.0000f)));
	
	g.setColour (Colour (0,0,0));
	g.fillRect ((float) (proportionOfWidth (0.0500f)), 
				(float) (proportionOfHeight (0.0500f)), 
				(float) (proportionOfWidth (0.9000f)), 
				18.0f);
}

void DeviceTabComponent::resized()
{
    
    const int h = 18;
	const int space = 6;
	const int dh = h + space;
	int y = proportionOfHeight (0.0500f) + 18 + space;
    
    ScopedPointer<Font> f(new Font(setConnectedDevice.getFont ()));
    int width = f->getStringWidth(setConnectedDevice.getText() );
    setConnectedDevice.setBounds(proportionOfWidth (0.0500f),
                                y + dh,
                                width + 10, h);
        
    devices->setBounds(proportionOfWidth (0.5800f) - 38, y + dh, 100, 18.0f);
    
    
    f = new Font(setListenPortLabel.getFont ());
    width = f->getStringWidth(setListenPortLabel.getText() );
    setListenPortLabel.setBounds(proportionOfWidth (0.0500f),
                                y + (dh*2),
                                width + 10, h);
    setListenPort.setBounds(proportionOfWidth(0.5800f) - 38, y + (dh*2), 100, 18.0f);
    
    
    f = new Font(setHostPortLabel.getFont ());
    width = f->getStringWidth(setHostPortLabel.getText() );
    setHostPortLabel.setBounds(proportionOfWidth (0.0500f),
                                 y + (dh*3),
                                 width + 10, h);
    setHostPort.setBounds(proportionOfWidth(0.5800f) - 38, y + (dh*3), 100, 18.0f);
}

void DeviceTabComponent::textEditorReturnKeyPressed (TextEditor &editor)
{
    //send OSC to set /sys/prefix
    DBG("prefix changed...");
}