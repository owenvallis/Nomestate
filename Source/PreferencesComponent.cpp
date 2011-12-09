/*
  ==============================================================================

    PreferencesComponent.cpp
    Created: 4 Dec 2011 11:08:43am
    Author:  Owen Vallis

  ==============================================================================
*/

#include "PreferencesComponent.h"
#include "MidiIOManagerComponent.h"
#include "AbletonStyleOSCComponent.h"

//==============================================================================
PreferencesComponent::PreferencesComponent (SignalCore& sCore, MidiIODeviceManager& deviceManager) 
{
	addAndMakeVisible(prefTabs = new TabbedComponent(TabbedButtonBar::TabsAtLeft) );
	prefTabs->addTab("MIDI I/O", Colour(0xff7f8993), new MidiIOManagerComponent(deviceManager), true);
    prefTabs->addTab("OSC", Colour(0xff7f8993), new AbletonStyleOSCComponent(), true);                           
    prefTabs->setCurrentTabIndex (0);
    
    
	setSize(450, 400);
    
}

PreferencesComponent::~PreferencesComponent()
{
    
}

//==============================================================================
void PreferencesComponent::paint (Graphics& g)
{
	g.fillAll (Colour(24,30,35));	

}

void PreferencesComponent::resized()
{
	prefTabs->setBounds (0, 10, getWidth() - 10, getHeight() - 20);
	prefTabs->getTabContentComponent(0)->setBounds(5 + prefTabs->getTabBarDepth (), 5,
                                                   prefTabs->getWidth() - prefTabs->getTabBarDepth () - 10,
                                                   prefTabs->getHeight() - 10);

}
