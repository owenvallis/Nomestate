/*
  ==============================================================================

    OSCMessage.h
    Created: 13 Oct 2011 11:57:04pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __OSCMESSAGE_H_97E7DD49__
#define __OSCMESSAGE_H_97E7DD49__

#include "../JuceLibraryCode/JuceHeader.h"
#include "OSCArg.h"
#include <vector>

using namespace std;

class OSCMessage {
    
public:
    
	OSCMessage();
	~OSCMessage();
    
	OSCMessage( const OSCMessage& other ){ 
        copy ( other ); 
    }
    
	OSCMessage& operator= ( const OSCMessage& other ) { 
        return copy( other ); 
    }
    
	// for operator= and copy constructor
	OSCMessage& copy( const OSCMessage& other );
    
	// clear this message, erase all contents
	void clear();
    
	// return the address
	String getAddress() const { return address; }
    
	// return the remote ip
	String getRemoteIp() { return remote_host; }
	// return the remote port
	int getRemotePort() { return remote_port; }
    
	// return number of argumentsļ
	int getNumArgs() const;
	// return argument type code for argument # index
	SignalOSCArgType getArgType( int index ) const;
	// return argument type name as String
	// - either "int", "float", or "String"
	String getArgTypeName( int index ) const;
    
	// get the argument with the given index as an int, float, or String
	// ensure that the type matches what you're requesting
	// (eg for an int argument, getArgType(index)==OF_TYPE_INT32
	// or getArgTypeName(index)=="int32")
	int32_t getArgAsInt32( int index ) const;
	float getArgAsFloat( int index ) const;
	String getArgAsString( int index ) const;
    
	// message construction
	void setAddress( String _address ) { address = _address; };
    
	// host and port of the remote endpoint
	void setRemoteEndpoint( String host, int port ) { remote_host = host; remote_port = port; }
	void addIntArg( int32_t argument );
	void addFloatArg( float argument );
	void addStringArg( String argument );
    
    
private:
    
	String address;
	vector<OSCArg*> args;
    
	String remote_host;
	int remote_port;
    
};


#endif  // __OSCMESSAGE_H_97E7DD49__
