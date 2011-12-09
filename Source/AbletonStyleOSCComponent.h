/*
  ==============================================================================

    AbletonStyleOSCComponent.h
    Created: 5 Dec 2011 12:16:23pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __ABLETONSTYLEOSCCOMPONENT_H_3A13D744__
#define __ABLETONSTYLEOSCCOMPONENT_H_3A13D744__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PropertiesManager.h"


class AbletonStyleOSCComponent  :   public Component,
                                    public TextEditor::Listener
{
public:
    //==============================================================================
    AbletonStyleOSCComponent ();
    ~AbletonStyleOSCComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    
    void textEditorTextChanged (TextEditor &editor){};
    void textEditorReturnKeyPressed (TextEditor &editor);
    void textEditorEscapeKeyPressed (TextEditor &editor){};
    void textEditorFocusLost (TextEditor &editor){};
    
private:
    
    TextEditor       setOSCPrefix;    
    Label            setOSCPrefixLabel;
    
    ScopedPointer<ChoicePropertyComponent>    devices;
    Label            setConnectedDevice;

    
    StringArray      deviceNames;
    Array<var>       connectedDevices;

};





#endif  // __ABLETONSTYLEOSCCOMPONENT_H_3A13D744__
