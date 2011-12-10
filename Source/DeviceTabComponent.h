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
                              public TextEditor::Listener
{
public:
    //==============================================================================
    DeviceTabComponent ();
    ~DeviceTabComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    
    void textEditorTextChanged (TextEditor &editor){};
    void textEditorReturnKeyPressed (TextEditor &editor);
    void textEditorEscapeKeyPressed (TextEditor &editor){};
    void textEditorFocusLost (TextEditor &editor){};
    
private:
        
    ScopedPointer<ChoicePropertyComponent>  devices;
    Label                                   setConnectedDevice;
    
    ScopedPointer<ChoicePropertyComponent>  rotation;
    Label                                   setRotationLabel;
    
    TextEditor                              setListenPort;    
    Label                                   setListenPortLabel;
    TextEditor                              setHostPort;    
    Label                                   setHostPortLabel;
    
    StringArray                             deviceNames;
    Array<var>                              connectedDevices;
    
    StringArray                             rotationNames;
    Array<var>                              rotationNamesVars;
    
    void setupRotationList();

};





#endif  // __DeviceTabComponent_H_3A13D744__
