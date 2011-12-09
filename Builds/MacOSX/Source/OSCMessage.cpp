/*
  ==============================================================================

    OSCMessage.cpp
    Created: 13 Oct 2011 11:57:04pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "OSCMessage.h"
#include <iostream>
#include <assert.h>

OSCMessage::OSCMessage() { }

OSCMessage::~OSCMessage(){
	clear();
}

void OSCMessage::clear() {
    
	for ( unsigned int i=0; i<args.size(); ++i )
		delete args[i];
	args.clear();
	address = "";
    
}

int OSCMessage::getNumArgs() const {
    
	return (int)args.size();
    
}

SignalOSCArgType OSCMessage::getArgType( int index ) const {
    
    if ( index >= (int)args.size() ) {
        fprintf(stderr,"OSCMessage::getArgType: index %d out of bounds\n", index );
        return OSC_TYPE_INDEXOUTOFBOUNDS;
    }
    else
        return args[index]->getType();
    
}

String OSCMessage::getArgTypeName( int index ) const {
    
    if ( index >= (int)args.size() ) {
        fprintf(stderr,"OSCMessage::getArgTypeName: index %d out of bounds\n", index );
        return "INDEX OUT OF BOUNDS";
    }
    
    else
        return args[index]->getTypeName();
    
}

int32_t OSCMessage::getArgAsInt32( int index ) const {
    
	if ( getArgType(index) != OSC_TYPE_INT32 ) {
	    if ( getArgType( index ) == OSC_TYPE_FLOAT ) {
            fprintf(stderr, "OSCMessage:getArgAsInt32: warning: converting int32 to float for argument %i\n", index );
            return ((SignalOSCArgFloat*)args[index])->get();
        }
        
        else {
            fprintf(stderr, "OSCMessage:getArgAsInt32: error: argument %i is not a number\n", index );
            return 0;
        }
	}
	else
        return ((SignalOSCArgInt32*)args[index])->get();
    
}


float OSCMessage::getArgAsFloat( int index ) const {
    
	if ( getArgType(index) != OSC_TYPE_FLOAT ) {
	    if ( getArgType( index ) == OSC_TYPE_INT32 ) {
            fprintf(stderr, "OSCMessage:getArgAsFloat: warning: converting float to int32 for argument %i\n", index );
            return ((SignalOSCArgInt32*)args[index])->get();
        }
        
        else {
            fprintf(stderr, "OSCMessage:getArgAsFloat: error: argument %i is not a number\n", index );
            return 0;
        }
	}
	else
        return ((SignalOSCArgFloat*)args[index])->get();
    
}


String OSCMessage::getArgAsString( int index ) const {
    
    if ( getArgType(index) != OSC_TYPE_STRING ) {
        
	    if ( getArgType( index ) == OSC_TYPE_FLOAT ) {
            char buf[1024];
            sprintf(buf,"%f",((SignalOSCArgFloat*)args[index])->get() );
            fprintf(stderr, "OSCMessage:getArgAsString: warning: converting float to string for argument %i\n", index );
            return buf;
        }
        
	    else if ( getArgType( index ) == OSC_TYPE_INT32 ) {
            char buf[1024];
            sprintf(buf,"%i",((SignalOSCArgInt32*)args[index])->get() );
            fprintf(stderr, "OSCMessage:getArgAsString: warning: converting int32 to string for argument %i\n", index );
            return buf;
        }
        
        else {
            fprintf(stderr, "OSCMessage:getArgAsString: error: argument %i is not a string\n", index );
            return "";
        }
        
	}
    
	else
        return ((SignalOSCArgString*)args[index])->get();
    
}

void OSCMessage::addIntArg( int32_t argument ) {
	args.push_back( new SignalOSCArgInt32( argument ) );
}

void OSCMessage::addFloatArg( float argument ) {
	args.push_back( new SignalOSCArgFloat( argument ) );
}

void OSCMessage::addStringArg( String argument ) {
	args.push_back( new SignalOSCArgString( argument ) );
}


OSCMessage& OSCMessage::copy( const OSCMessage& other ) {
    
	clear();
    
	address = other.address;
    
	remote_host = other.remote_host;
	remote_port = other.remote_port;
    
	// copy arguments
	for ( int i=0; i<(int)other.args.size(); ++i ) {
        
		SignalOSCArgType argType = other.getArgType( i );
		if ( argType == OSC_TYPE_INT32 )
			args.push_back( new SignalOSCArgInt32( other.getArgAsInt32( i ) ) );
        
		else if ( argType == OSC_TYPE_FLOAT )
			args.push_back( new SignalOSCArgFloat( other.getArgAsFloat( i ) ) );
        
		else if ( argType == OSC_TYPE_STRING )
			args.push_back( new SignalOSCArgString( other.getArgAsString( i ) ) );
        
		else {
			assert( false && "bad argument type" );
		}
        
	}
    
	return *this;
    
}
