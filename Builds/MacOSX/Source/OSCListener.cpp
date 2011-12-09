/*
  ==============================================================================

    OSCListener.cpp
    Created: 13 Oct 2011 11:32:49pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "OSCListener.h"
#include <iostream>
#include <assert.h>

OSCListener::OSCListener() : Thread("OSC Listener") {	
    isActive = false;
}

OSCListener::~OSCListener() {	
    stopListening();
}

void OSCListener::startListening( String _addr, int _port ) {	
    
    DBG("OSCListener::startListening()"); 
    
	socketHasShutdown = false;
    
    socket = new UdpListeningReceiveSocket( IpEndpointName( _addr.toUTF8() , _port), this);

	isActive = true;
    
    if (!isThreadRunning()){
        startThread();
    }
    
}

void OSCListener::run() {
    socket->Run();
}


void OSCListener::stopListening() {
        
    socket->AsynchronousBreak(); // this is fucked... 
    
    stopThread(2000);

    delete socket;
    socket = NULL;
        
}

void OSCListener::ProcessMessage( const osc::ReceivedMessage &m, const IpEndpointName& remoteEndpoint ) {	
    
    // convert the message to an OSCMessage
	OSCMessage* myMessage = new OSCMessage();
    
	// set the address
	myMessage->setAddress( m.AddressPattern() );
    
	// set the sender ip/host
	char endpoint_host[ IpEndpointName::ADDRESS_STRING_LENGTH ];
	remoteEndpoint.AddressAsString( endpoint_host );
    myMessage->setRemoteEndpoint( endpoint_host, remoteEndpoint.port );
    
    try {
    
        // transfer the arguments
        for ( osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin(); arg != m.ArgumentsEnd(); ++arg ) {
            if ( arg->IsInt32() )
                myMessage->addIntArg( arg->AsInt32Unchecked() );
            else if ( arg->IsFloat() )
                myMessage->addFloatArg( arg->AsFloatUnchecked() );
            else if ( arg->IsString() )
                myMessage->addStringArg( arg->AsStringUnchecked() );
            else {
                DBG("OSCListener::ProcessMessage() - Message argument is not a recognizable type."); 
            }
        }
        
        // add incoming message on to the queue
        messages.push_back( myMessage );
        
        handleOSC(); 
        
    } catch(osc::Exception& e) {
        DBG("OSCListener::ProcessMessage() - Parsing error " << m.AddressPattern() << ": " << e.what() << "\n");
    }
    
}

bool OSCListener::hasWaitingMessages() {	

	// check the length of the queue
	int queue_length = (int)messages.size();

	// return whether we have any messages
	return queue_length > 0;
    
}

bool OSCListener::getNextMessage( OSCMessage* message ) {	
    
	// check if there are any to be got
	if (messages.size() == 0) {
		return false;
	}
    
	// copy the message from the queue to message
	OSCMessage* src_message = messages.front();
	message->copy( *src_message );
    
	// now delete the src message
	delete src_message;
    
	// and remove it from the queue
	messages.pop_front();
    
	// return success
	return true;
    
}


bool OSCListener::isListening(){
	return isActive;	
}