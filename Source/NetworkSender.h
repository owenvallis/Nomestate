 /*
  ==============================================================================

    NetworkSender.h
    Created: 10 Oct 2011 10:02:38pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __NETWORKSENDER_H_16006496__
#define __NETWORKSENDER_H_16006496__

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSCBroadcaster.h"
#include "Signal.h"
#include <iostream>

//forward declaration resolves the circular dependancy
class MessageCenter;

class NetworkSender : public OSCBroadcaster,
                      public ValueListener
{
public:
    
    NetworkSender();
    ~NetworkSender();
    
    void handleSignal(Signal s); 
    
    void valueChanged(Value& value);
    
private:
    Value serverHostPort;
    Value prefix;
    Value rotation;

     
};


#endif  // __NETWORKSENDER_H_16006496__
