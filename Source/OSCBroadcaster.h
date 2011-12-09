/*
  ==============================================================================

    OSCBroadcaster.h
    Created: 13 Oct 2011 11:32:31pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __OSCBROADCASTER_H_DEA434B0__
#define __OSCBROADCASTER_H_DEA434B0__

class UdpTransmitSocket;

#include "../JuceLibraryCode/JuceHeader.h"

#include "OscTypes.h"
#include "OscOutboundPacketStream.h"

#include "OSCBundle.h"
#include "OSCMessage.h"


class OSCBroadcaster {
    
public:
	OSCBroadcaster();
	~OSCBroadcaster();
    
	/// send messages to hostname and port
	void setup( String hostname, int port );
    
	/// send the given message
	void sendMessage( OSCMessage& message );
    
	/// send the given bundle
	void sendBundle( OSCBundle& bundle );
    
private:
	void shutdown();
    
	// helper methods for constructing messages
	void appendBundle( OSCBundle& bundle, osc::OutboundPacketStream& p );
	void appendMessage( OSCMessage& message, osc::OutboundPacketStream& p );
    
	UdpTransmitSocket* socket;
    
};

#endif  // __OSCBROADCASTER_H_DEA434B0__
