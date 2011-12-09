/*
  ==============================================================================

    PropertiesManager.cpp
    Created: 6 Nov 2011 9:23:02pm
    Author:  Owen Vallis

  ==============================================================================
*/

#include "PropertiesManager.h"

PropertiesManager::PropertiesManager()  :   connectedDevices(Identifier("connectedDevices")),                                     
                                            buttonMode("buttonMode", "ButtonMode", "ButtonMode"),
                                            pressureMode("pressureMode", "Pressure", "Pressure" ),
                                            colourEditor("colourEditor","Colour","Colour")
                                            
{
    connectedDevices.setProperty(Identifier("currentdevice"), "No Device Connected", NULL);
    connectedDevices.setProperty(Identifier("currentHostPort"), 8080, NULL);
    connectedDevices.setProperty(Identifier("currentListenPort"), 8000, NULL);
    
    mainPropertyGroup = new PropertyGroup("mainGroup","ButtonProperties");
    mainPropertyGroup->addProperty(buttonMode);
    mainPropertyGroup->addProperty(pressureMode);
    mainPropertyGroup->addProperty(colourEditor);
    propertyGroupLibrary.registerPropertyGroup(mainPropertyGroup);
    
    for (int i=0; i<64; i++) {
        buttonPropertyCollection.add(new ButtonPropertyContainer(i)); 
    }
    //std::cout<< buttonPropertyCollection.size() << std::endl;
    
}

PropertiesManager::~PropertiesManager()
{
    // this ensures that no dangling pointers are left when the
    // singleton is deleted.
    clearSingletonInstance();
}

juce_ImplementSingleton (PropertiesManager);

void PropertiesManager::setButtonsBeingEdited(Array<int> buttonsBeingEdited)
{
    _buttonsBeingEdited.clear();
    
    for (int i = 0; i < buttonsBeingEdited.size(); i++) {
        _buttonsBeingEdited.add(buttonPropertyCollection[buttonsBeingEdited[i]]);
    }
} 

void PropertiesManager::registerButton(NomeButton* button)
{
    buttonPropertyBroadcaster.add(button);
}

void PropertiesManager::deregisterButton(NomeButton* button)
{
    buttonPropertyBroadcaster.remove(button);
}

void PropertiesManager::deregisterAllButtons()
{
    buttonPropertyBroadcaster.clear();
}