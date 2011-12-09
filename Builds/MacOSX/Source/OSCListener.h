/*
  ==============================================================================

    OSCListener.h
    Created: 13 Oct 2011 11:32:49pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __OSCLISTENER_H_FDF951A6__
#define __OSCLISTENER_H_FDF951A6__

#include "../JuceLibraryCode/JuceHeader.h"

#include "OscTypes.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"
#include <deque>

#include "OSCMessage.h"

class OSCListener : public osc::OscPacketListener, 
                    public Thread 
{
    
public:
    
	OSCListener();
	~OSCListener();
    
	void startListening(String, int);

	bool hasWaitingMessages();

	bool getNextMessage( OSCMessage* );
    
    bool isListening();
    
    bool isActive;
    
    virtual void handleOSC() {};  
    
protected:
    
	UdpListeningReceiveSocket* socket;
    
	/// process an incoming osc message and add it to the queue
	virtual void ProcessMessage( const osc::ReceivedMessage &m, const IpEndpointName& remoteEndpoint );
    
private:
    
    void run();
    
	void stopListening();
    
	std::deque<OSCMessage*> messages;

	bool socketHasShutdown;
    
};



#endif  // __OSCLISTENER_H_FDF951A6__
