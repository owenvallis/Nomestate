/*
  ==============================================================================

    SignalModifier.h
    Created: 6 Nov 2011 8:47:28pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __SIGNALMODIFIER_H_C8A4CA56__
#define __SIGNALMODIFIER_H_C8A4CA56__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Signal.h"
#include "PropertiesManager.h"

//forward declaration resolves the circular dependancy
class MessageCenter;

class SignalModifier {

public:
    SignalModifier(MessageCenter &center);
    ~SignalModifier();
    
    void setModel(PropertiesManager &pManager) { _mpManager = &pManager;}
    void handleSignal(Signal s);
    
    bool convertToToggle(Signal &s);
    bool convertToTrigger(Signal &s);
    bool convertToNote(Signal &s);
    
private:
    
    MessageCenter *_mCenter;
    
    PropertiesManager* _mpManager;
    
    bool convertSignal(Signal &s);
    
    int toggleState;
    
};



#endif  // __SIGNALMODIFIER_H_C8A4CA56__
