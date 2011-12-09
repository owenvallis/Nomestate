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

#include "MessageCenter.h"
#include "MIDISender.h"
#include "SignalModifier.h"
#include "NetworkSender.h"


class SignalCore {
    
public:
    
    SignalCore();
    ~SignalCore(); 
    
    SignalModifier* getsignalModifier() { return &_sigModifier; }
    
private:
    MessageCenter   _mCenter;
    SignalModifier  _sigModifier;

    NetworkReceiver _nRecv;
    NetworkSender   _nSender;
    
    MIDISender      _MIDISender;
    
};


#endif  // __SIGNALCORE_H_63283C81__
