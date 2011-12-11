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
                          public ValueTree::Listener
{
public:
    PropertiesManager           ();
    ~PropertiesManager          ();
    
    juce_DeclareSingleton (PropertiesManager, false);
    
    PropertyGroupLibrary* getPropertyGroupLibrary () {return &propertyGroupLibrary; };
    PropertyGroup::ComponentFactory* getPropertyGroupFactory () {return &propertyFactory; };
    
    void setButtonsBeingEdited(Array<int> buttonsBeingEdited);
    
    Array<PropertyGroup::Container*> getButtonsBeingEdited() { return _buttonsBeingEdited; };
    void clearButtonsBeingEdited() { _buttonsBeingEdited.clear(); }
    
    void registerButton(NomeButton* button);
    
    void deregisterButton(NomeButton* button);
    
    void deregisterAllButtons();
    
    void valueTreePropertyChanged   (ValueTree& treeWhosePropertyHasChanged,
                                        const Identifier& property);
    void valueTreeChildAdded        (ValueTree& parentTree,
                                        ValueTree& childWhichHasBeenAdded);
    void valueTreeChildRemoved      (ValueTree& parentTree,
                                     ValueTree& childWhichHasBeenRemoved);
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved);
    void valueTreeParentChanged     (ValueTree& treeWhoseParentHasChanged);
    
    
    ButtonPropertyContainer* getButtonPropertyContainer(int _buttonID) {return buttonPropertyCollection[_buttonID];}
    
    ValueTree                       connectedDevices;
        
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertiesManager);
    
};


#endif  // __PROPERTIESMANAGER_H_EC1B2AD7__
