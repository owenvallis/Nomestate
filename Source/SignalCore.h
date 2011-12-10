/*
  ==============================================================================

    SignalCore.h
    Created: 10 Oct 2011 10:00:33pm
    Author:  Dimitri Diakopoulos
 
    << Follows the Facade Pattern >> 

  ==============================================================================
*/

// 
#ifndef __SIGNALCORE_H_63283C81__
#define __SIGNALCORE_H_63283C81__

#include "MidiIODeviceManager.h"
#include "MessageCenter.h"
#include "SignalModifier.h"
#include "MIDISender.h"
#include "MIDIReceiver.h"
#include "NetworkSender.h"
#include "NetworkReceiver.h"


class SignalCore : public ValueListener {
    
public:
    
    SignalCore(MidiIODeviceManager &pMidiIODeviceManager);
    ~SignalCore(); 
    
    MessageCenter* getMessageCenter() { return &_mCenter; }
    
    
    void   valueChanged(Value& value);
    
private:
    MessageCenter   _mCenter;
    SignalModifier  _sigModifier;

    MIDIReceiver    _MIDIReceiver;
    MIDISender      _MIDISender;

    NetworkReceiver _nRecv;
    NetworkSender   _nSender;
    
    OwnedArray<Value> buttonColours;
};


#endif  // __SIGNALCORE_H_63283C81__
