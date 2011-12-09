/*
  ==============================================================================

    OSCBroadcaster.cpp
    Created: 13 Oct 2011 11:32:31pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSCBroadcaster.h"
#include "UdpSocket.h"
#include <assert.h>

OSCBroadcaster::OSCBroadcaster() {
	socket = NULL;
}

OSCBroadcaster::~OSCBroadcaster() {
    
	if ( socket )
		shutdown();
    
}

void OSCBroadcaster::setup( String hostname, int port ) {
    
	if ( socket )
		shutdown();
	
	socket = new UdpTransmitSocket( IpEndpointName( hostname.toUTF8(), port ) );
    
}

void OSCBroadcaster::shutdown() {
    
	if ( socket )
		delete socket;
	socket = NULL;
    
}

void OSCBroadcaster::sendBundle( OSCBundle& bundle ) {
    
	static const int OUTPUT_BUFFER_SIZE = 32768;
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );
    
	// serialise the bundle
	appendBundle( bundle, p );
    
	socket->Send( p.Data(), p.Size() );
    
}

void OSCBroadcaster::sendMessage( OSCMessage& message ) {
    
	static const int OUTPUT_BUFFER_SIZE = 16384;
	char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
    
	// serialise the message
	p << osc::BeginBundleImmediate;
	appendMessage( message, p );
	p << osc::EndBundle;
    
	socket->Send( p.Data(), p.Size() );
    
}

void OSCBroadcaster::appendBundle( OSCBundle& bundle, osc::OutboundPacketStream& p ) {
    
	// recursively serialise the bundle
	p << osc::BeginBundleImmediate;
    
	for ( int i=0; i<bundle.getBundleCount(); i++ ) {
		appendBundle( bundle.getBundleAt( i ), p );
	}
    
	for ( int i=0; i<bundle.getMessageCount(); i++ ) {
		appendMessage( bundle.getMessageAt( i ), p );
	}
	p << osc::EndBundle;
    
}

void OSCBroadcaster::appendMessage( OSCMessage& message, osc::OutboundPacketStream& p ) {
    
    p << osc::BeginMessage( message.getAddress().toUTF8() );
    
	for ( int i=0; i< message.getNumArgs(); ++i ) {
        
		if ( message.getArgType(i) == OSC_TYPE_INT32 )
			p << message.getArgAsInt32( i );
        
		else if ( message.getArgType( i ) == OSC_TYPE_FLOAT )
			p << message.getArgAsFloat( i );
        
		else if ( message.getArgType( i ) == OSC_TYPE_STRING )
			p << message.getArgAsString( i ).toUTF8();
        
		else {
			assert( false && "bad argument type" );
		}
        
	}
    
	p << osc::EndMessage;
    
}

