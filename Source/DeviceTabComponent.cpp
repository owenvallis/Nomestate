/*
  ==============================================================================

    DeviceTabComponent.cpp
    Created: 5 Dec 2011 12:16:23pm
    Author:  Owen Vallis

  ==============================================================================
*/

#include "DeviceTabComponent.h"

DeviceTabComponent::DeviceTabComponent() :  setConnectedDevice(String::empty, "Set Connected Device:"),
                                            setRotationLabel(String::empty, "Rotation:"),                                            
                                            setListenPort(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue(Identifier("currentListenPort"), NULL), " ", 5, false),
                                            setListenPortLabel(String::empty, "Listen Port:"),
                                            setHostPort(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue(Identifier("currentHostPort"), NULL), " ", 5, false),
                                            setHostPortLabel(String::empty, "Host Port:")
                                            
                                                        
{   
    
    addAndMakeVisible(&setListenPort);
    
    
    addAndMakeVisible(&setListenPortLabel);
    setListenPortLabel.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setListenPortLabel.setJustificationType (Justification::centredLeft);
    setListenPortLabel.setEditable (false, false, false);
    setListenPortLabel.setColour (TextEditor::textColourId, Colours::black);
    setListenPortLabel.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    addAndMakeVisible(&setHostPort);
    
    addAndMakeVisible(&setHostPortLabel);
    setHostPortLabel.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setHostPortLabel.setJustificationType (Justification::centredLeft);
    setHostPortLabel.setEditable (false, false, false);
    setHostPortLabel.setColour (TextEditor::textColourId, Colours::black);
    setHostPortLabel.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    
    setupDeviceList();
  
    addAndMakeVisible( devices = new ChoicePropertyComponent(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL), 
                                                              " ", 
                                                             deviceNames, 
                                                             connectedDevices));
    addAndMakeVisible (&setConnectedDevice);
    setConnectedDevice.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setConnectedDevice.setJustificationType (Justification::centredLeft);
    setConnectedDevice.setEditable (false, false, false);
    setConnectedDevice.setColour (TextEditor::textColourId, Colours::black);
    setConnectedDevice.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    setupRotationList();
    
    addAndMakeVisible( rotation = new ChoicePropertyComponent(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("rotation", NULL), 
                                                              " ", 
                                                              rotationNames, 
                                                              rotationNamesVars));
    addAndMakeVisible (&setRotationLabel);
    setRotationLabel.setFont (Font (Font::getDefaultSansSerifFontName (), 11.5000f, Font::bold));
    setRotationLabel.setJustificationType (Justification::centredLeft);
    setRotationLabel.setEditable (false, false, false);
    setRotationLabel.setColour (TextEditor::textColourId, Colours::black);
    setRotationLabel.setColour (TextEditor::backgroundColourId, Colour (0x0));
    
    PropertiesManager::getInstance()->connectedDevices.addListener(this);
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
        
    devices->setBounds(proportionOfWidth (0.2610f), y + dh, 250, 20);
    
    setRotationLabel.setBounds(proportionOfWidth (0.0500f),
                                 y + (dh*2),
                                 width + 10, h);
    
    rotation->setBounds(proportionOfWidth (0.2610f), y + (dh*2), 250, 20);
    
    
    f = new Font(setListenPortLabel.getFont ());
    width = f->getStringWidth(setListenPortLabel.getText() );
    setListenPortLabel.setBounds(proportionOfWidth (0.0500f),
                                y + (dh*3),
                                width + 10, h);
    setListenPort.setBounds(proportionOfWidth (0.2610f), y + (dh*3), 250, 20.0f);
    
    
    f = new Font(setHostPortLabel.getFont ());
    width = f->getStringWidth(setHostPortLabel.getText() );
    setHostPortLabel.setBounds(proportionOfWidth (0.0500f),
                                 y + (dh*4),
                                 width + 10, h);
    setHostPort.setBounds(proportionOfWidth (0.2610f), y + (dh*4), 250, 20.0f);
}

void DeviceTabComponent::setupRotationList()
{
    rotationNames.add("top");
    rotationNames.add("right");
    rotationNames.add("bottom");
    rotationNames.add("left");
    for (int i = 0; i<rotationNames.size(); i++) {
        rotationNamesVars.add(var(i*90));
    }
}

void DeviceTabComponent::setupDeviceList()
{
    deviceNames.clear();
    connectedDevices.clear();
    
    for (int i = 0; i < PropertiesManager::getInstance()->connectedDevices.getNumChildren(); i++) {
        Value value(PropertiesManager::getInstance()->connectedDevices.getChild(i).getPropertyAsValue(Identifier("deviceName"), NULL));
        deviceNames.add(value.toString());
        connectedDevices.add(value.getValue());
    }
}

void DeviceTabComponent::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    if(property == Identifier("deviceName"))
    {
        setupDeviceList();
        
        const MessageManagerLock mmLock;
        
        addAndMakeVisible (devices = new ChoicePropertyComponent(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL), 
                                                                 " ", deviceNames, connectedDevices));
        
        resized();
        
        DBG(PropertiesManager::getInstance()->connectedDevices.getNumChildren());
        DBG(deviceNames.size());
        if(deviceNames.size() > 0)
            DBG(deviceNames[0]);
    }
}

// This method is called when a child sub-tree is removed. 
void DeviceTabComponent::valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved) 
{
    if(parentTree == PropertiesManager::getInstance()->connectedDevices)
    {
        setupDeviceList();
        
        const MessageManagerLock mmLock;
        
        addAndMakeVisible (devices = new ChoicePropertyComponent(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL), 
                                                                 " ", deviceNames, connectedDevices));
        
        resized();
        
        DBG(PropertiesManager::getInstance()->connectedDevices.getNumChildren());
        DBG(deviceNames.size());
        if(deviceNames.size() > 0)
            DBG(deviceNames[0]);
    }
}