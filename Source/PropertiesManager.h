/*
  ==============================================================================

    PropertiesManager.h
    Created: 6 Nov 2011 9:23:02pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __PROPERTIESMANAGER_H_EC1B2AD7__
#define __PROPERTIESMANAGER_H_EC1B2AD7__

#include "../JuceLibraryCode/JuceHeader.h"

#include "PropertyGroup.h"
#include "ButtonPropertyContainer.h"
#include "NomeButton.h"

extern ApplicationProperties* appProperties;

class PropertiesManager : public DeletedAtShutdown,
                          public ValueListener
{
public:
    PropertiesManager           ();
    ~PropertiesManager          ();
    
    juce_DeclareSingleton (PropertiesManager, false);
    
    PropertyGroupLibrary* getPropertyGroupLibrary () {return &propertyGroupLibrary; };
    PropertyGroup::ComponentFactory* getPropertyGroupFactory () {return &propertyFactory; };
    
    void updatePropertyGroupDescriptors();
    
    void setButtonsBeingEdited(Array<int> buttonsBeingEdited);
    
    Array<PropertyGroup::Container*> getButtonsBeingEdited() { return _buttonsBeingEdited; };
    void clearButtonsBeingEdited() { _buttonsBeingEdited.clear(); }
    void registerButton(NomeButton* button);
    void deregisterButton(NomeButton* button);
    void deregisterAllButtons();
    
    void valueChanged(Value& value);
    
    ButtonPropertyContainer* getButtonPropertyContainer(int _buttonID) {return buttonPropertyCollection[_buttonID];}
    
    ValueTree                       connectedDevices;
    Value                           currentDevice;
        
private:
    

    ListenerList<NomeButton>        buttonPropertyBroadcaster;

    PropertyDescriptor              buttonMode;
    PropertyDescriptor              pressureMode;
    PropertyDescriptor              colourEditor;
    PropertyGroup*                  nomePropertyGroup;
    PropertyGroup*                  chronomePropertyGroup;
    PropertyGroupLibrary            propertyGroupLibrary;
    PropertyGroup::ComponentFactory propertyFactory;
    
    OwnedArray<ButtonPropertyContainer> buttonPropertyCollection;
    
	Array<PropertyGroup::Container*> _buttonsBeingEdited;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertiesManager);
    
};


#endif  // __PROPERTIESMANAGER_H_EC1B2AD7__
