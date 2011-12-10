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
    DeviceTabComponent (SignalCore& sCore);
    ~DeviceTabComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    
    void textEditorTextChanged (TextEditor &editor){};
    void textEditorReturnKeyPressed (TextEditor &editor);
    void textEditorEscapeKeyPressed (TextEditor &editor){};
    void textEditorFocusLost (TextEditor &editor){};
    
private:
    
    SignalCore*                 _sCore;
    
    ScopedPointer<ChoicePropertyComponent>    devices;
    Label                                     setConnectedDevice;
    
    TextEditor                              setListenPort;    
    Label                       setListenPortLabel;
    TextEditor                  setHostPort;    
    Label                       setHostPortLabel;
    
    StringArray                 deviceNames;
    Array<var>                  connectedDevices;

};





#endif  // __DeviceTabComponent_H_3A13D744__
