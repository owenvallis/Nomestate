/*
  ==============================================================================

    Signal.h
    Created: 10 Oct 2011 10:04:02pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __SIGNAL_H_1E2F7F69__
#define __SIGNAL_H_1E2F7F69__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Message.h"
#include "MessageArg.h"
#include <vector>

class Signal : public Msg, public ReferenceCountedObject {
    
public:
    
    Signal();
    ~Signal(); 
    
    Signal(String cmd, String ori); 
    
    Signal(const Signal& other) { copy (other); }
    
	virtual Signal& operator= ( const Signal& other ) { 
        return copy(other); 
    }
    
    void clear(); 
    
	virtual Signal& copy( const Signal& other );
    
    String command;
    String origin; 
    
    typedef ReferenceCountedObjectPtr<Signal> SignalP;
    
    JUCE_LEAK_DETECTOR(Signal);     
    
};


#endif  // __SIGNAL_H_1E2F7F69__
