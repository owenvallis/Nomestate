/*
  ==============================================================================

    DeviceTabComponent.h
    Created: 5 Dec 2011 12:16:23pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __DeviceTabComponent_H_3A13D744__
#define __DeviceTabComponent_H_3A13D744__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PropertiesManager.h"
#include "SignalCore.h"

class DeviceTabComponent  :   public Component,
                              public ValueTree::Listener
{
public:
    //==============================================================================
    DeviceTabComponent ();
    ~DeviceTabComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    
    // 	This method is called when a property of this node (or of one of its sub-nodes) has changed. 
    void 	valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
    //  This method is called when a child sub-tree is added. 
    void 	valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded) {}
    // This method is called when a child sub-tree is removed. 
    void 	valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved);
    // This method is called when a tree's children have been re-shuffled. 
    void 	valueTreeChildOrderChanged (ValueTree &parentTreeWhoseChildrenHaveMoved) {}
    // This method is called when a tree has been added or removed from a parent node. 
    void 	valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged) {}
    
private:
        
    ScopedPointer<ChoicePropertyComponent>  devices;
    Label                                   setConnectedDevice;
    
    ScopedPointer<ChoicePropertyComponent>  rotation;
    Label                                   setRotationLabel;
    
    TextPropertyComponent                   setListenPort;    
    Label                                   setListenPortLabel;
    TextPropertyComponent                   setHostPort;    
    Label                                   setHostPortLabel;
    
    StringArray                             deviceNames;
    Array<var>                              connectedDevices;
    
    StringArray                             rotationNames;
    Array<var>                              rotationNamesVars;
    
    void setupRotationList();
    void setupDeviceList();

};





#endif  // __DeviceTabComponent_H_3A13D744__
