/*
  ==============================================================================

    PreferencesComponent.cpp
    Created: 4 Dec 2011 11:08:43am
    Author:  Owen Vallis

  ==============================================================================
*/

#include "PreferencesComponent.h"
#include "MidiIOManagerComponent.h"
#include "DeviceTabComponent.h"

//==============================================================================
PreferencesComponent::PreferencesComponent (SignalCore& sCore, MidiIODeviceManager& deviceManager) 
{
	addAndMakeVisible(prefTabs = new TabbedComponent(TabbedButtonBar::TabsAtLeft) );
    prefTabs->addTab("Device", Colour(81,81,81), new DeviceTabComponent(), true);                           
	prefTabs->addTab("Midi", Colour(81,81,81), new MidiIOManagerComponent(deviceManager), true);
    prefTabs->setCurrentTabIndex (0);
    
    
	setSize(450, 400);
    
}

PreferencesComponent::~PreferencesComponent()
{
    
}

//==============================================================================
void PreferencesComponent::paint (Graphics& g)
{
	g.fillAll (Colour(25,25,25));	

}

void PreferencesComponent::resized()
{
	prefTabs->setBounds (0, 10, getWidth() - 10, getHeight() - 20);

}
