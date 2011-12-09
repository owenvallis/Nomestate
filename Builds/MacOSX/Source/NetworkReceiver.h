/*
  ==============================================================================

    NetworkReceiver.h
    Created: 10 Oct 2011 10:02:34pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __NETWORKRECEIVER_H_A93D66C4__
#define __NETWORKRECEIVER_H_A93D66C4__

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSCListener.h"
#include "Signal.h"
#include <iostream>

//forward declaration resolves the circular dependancy
class MessageCenter;

class NetworkReceiver : public OSCListener {
    
public:
    
    NetworkReceiver(MessageCenter &center); 
    ~NetworkReceiver();
    
    void handleOSC(); 
    void oscToSignal(OSCMessage msg); 
    
private:
    
    MessageCenter *_mCenter; 
    
    JUCE_LEAK_DETECTOR(NetworkReceiver);      
    
};


#endif  // __NETWORKRECEIVER_H_A93D66C4__
