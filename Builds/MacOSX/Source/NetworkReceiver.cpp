/*
  ==============================================================================

    NetworkReceiver.cpp
    Created: 10 Oct 2011 10:02:34pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "NetworkReceiver.h"

// Forward declaration fun. 
#include "MessageCenter.h"

NetworkReceiver::NetworkReceiver(MessageCenter &center) {
    
    _mCenter = &center; 
    
    startListening("localhost", 8000); 
    
}

NetworkReceiver::~NetworkReceiver() {
    
}

void NetworkReceiver::handleOSC() {

	while( this->hasWaitingMessages() ){
		OSCMessage m;
		this->getNextMessage( &m );
        oscToSignal(m); 
    }
    
}

void NetworkReceiver::oscToSignal(OSCMessage msg) {
    
    /* Strip slashes to find the command. This should be done with a proper regex library
     * and tested against a bunch of 'junk' strings. For now, this is a hack... */ 
    String cmd = File::createLegalFileName(msg.getAddress()); 
    
    // Find client IP from the message. 
    String origin = msg.getRemoteIp(); 
    
    // Find way of timestamping this signal. should log it. 
    DBG("NetworkReceiver::oscToSignal(" + cmd + ")"); 
    
    // reference counted Signal ( string command, string origin )
    Signal::SignalP mySignal = new Signal(cmd, origin);
    
    // if this an OSC button press, then lets ask for a MIDI_EVENT
    if(cmd == "boxgridkey" || cmd == "boxpress") {
        
        // set a MIDI_EVENT
        mySignal->command = "SIGNAL_MOD";
        
        // find our button position [0..63]
        int32_t buttonID = msg.getArgAsInt32(0) + ( msg.getArgAsInt32(1) * 8);
        
        // pack channel, button position (MIDI_NUM), and velocity
        mySignal->addIntArg(buttonID);
        mySignal->addIntArg(msg.getArgAsInt32(2));
    }
    
    _mCenter->handleSignal(*mySignal); 
}

