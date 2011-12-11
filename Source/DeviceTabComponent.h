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

class DeviceTabComponent  :   public Component
{
public:
    //==============================================================================
    DeviceTabComponent ();
    ~DeviceTabComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    
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

};





#endif  // __DeviceTabComponent_H_3A13D744__
