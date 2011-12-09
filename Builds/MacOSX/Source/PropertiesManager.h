/*
  ==============================================================================

    PropertiesManager.h
    Created: 6 Nov 2011 9:23:02pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __PROPERTIESMANAGER_H_EC1B2AD7__
#define __PROPERTIESMANAGER_H_EC1B2AD7__

#include "PropertyGroup.h"
#include "ButtonPropertyContainer.h"
#include "NomeButton.h"


class PropertiesManager
{
public:
    PropertiesManager           ();
    ~PropertiesManager          ();
    
    PropertyGroupLibrary* getPropertyGroupLibrary () {return &propertyGroupLibrary; };
    PropertyGroup::ComponentFactory* getPropertyGroupFactory () {return &propertyFactory; };
    
    void setButtonsBeingEdited(Array<int> buttonsBeingEdited);
    
    Array<PropertyGroup::Container*> getButtonsBeingEdited() { return _buttonsBeingEdited; };
    
    void registerButton(NomeButton* button);
    
    void deregisterButton(NomeButton* button);
    
    void deregisterAllButtons();
    
    ButtonPropertyContainer* getButtonPropertyContainer(int _buttonID) {return buttonPropertyCollection[_buttonID];}
        
private:
    
    ListenerList<NomeButton>        buttonPropertyBroadcaster;

    PropertyDescriptor              buttonMode;
    PropertyDescriptor              pressureMode;
    PropertyDescriptor              colourEditor;
    PropertyGroup*                  mainPropertyGroup;
    PropertyGroupLibrary            propertyGroupLibrary;
    PropertyGroup::ComponentFactory propertyFactory;
    
    OwnedArray<ButtonPropertyContainer> buttonPropertyCollection;
    
	Array<PropertyGroup::Container*> _buttonsBeingEdited;
};




#endif  // __PROPERTIESMANAGER_H_EC1B2AD7__
