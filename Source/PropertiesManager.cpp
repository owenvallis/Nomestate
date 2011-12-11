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
    connectedDevices.addListener(this);
    
    connectedDevices.setProperty(Identifier("currentdevice"), "No Device Connected", NULL);

    if (!appProperties->getUserSettings()->getFile().existsAsFile()) 
    {
        DBG("no setttings file, so we are initializing the settings");
        
        connectedDevices.setProperty(Identifier("currentHostPort"), 8080, NULL);
        connectedDevices.setProperty(Identifier("currentListenPort"), 8000, NULL);
        connectedDevices.setProperty(Identifier("rotation"), "right", NULL);
        
    } else {
        connectedDevices.setProperty(Identifier("currentHostPort"), appProperties->getUserSettings()->getValue("currentHostPort") , NULL);
        connectedDevices.setProperty(Identifier("currentListenPort"), appProperties->getUserSettings()->getValue("currentListenPort") , NULL);
        connectedDevices.setProperty(Identifier("rotation"), appProperties->getUserSettings()->getValue("rotation") , NULL);
    }
    
    mainPropertyGroup = new PropertyGroup("mainGroup","ButtonProperties");
    mainPropertyGroup->addProperty(buttonMode);
    mainPropertyGroup->addProperty(pressureMode);
    mainPropertyGroup->addProperty(colourEditor);
    propertyGroupLibrary.registerPropertyGroup(mainPropertyGroup);
    
    for (int i=0; i<64; i++) {
        buttonPropertyCollection.add(new ButtonPropertyContainer(i)); 
    }    
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

void PropertiesManager::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) 
{
    if(treeWhosePropertyHasChanged == connectedDevices && property != "currentdevice") 
    {
        appProperties->getUserSettings()->setValue(property.toString(), connectedDevices.getPropertyAsValue(property, NULL));
    
        appProperties->saveIfNeeded();
    }
}

void PropertiesManager::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    
}

void PropertiesManager::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved)
{
    
}

void PropertiesManager::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved)
{
    
}

void PropertiesManager::valueTreeParentChanged     (ValueTree& treeWhoseParentHasChanged)
{
    
}