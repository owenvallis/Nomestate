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
    
    void handleSignal(Signal s);
    
    bool convertToToggle(Signal &s);
    bool convertToTrigger(Signal &s);
    bool convertToNote(Signal &s);
    
    bool convertToTogglePressure(Signal &s);
    bool convertToTriggerPressure(Signal &s);
    bool convertToNotePressure(Signal &s);
    
private:
    
    MessageCenter *_mCenter;
        
    bool convertSignal(Signal &s);
    
    int lastPressValue;
    
};



#endif  // __SIGNALMODIFIER_H_C8A4CA56__
