/*
  ==============================================================================

    Signal.cpp
    Created: 10 Oct 2011 10:04:02pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "Signal.h"

Signal::Signal() {}

Signal::Signal(String cmd, String ori){
    command = cmd;
    origin = ori;
}

Signal::~Signal(){
    clear(); 
}

void Signal::clear(){
    
    command = ""; 
    origin = ""; 
    
    for ( unsigned int i=0; i<args.size(); ++i )
        delete args[i];

    args.clear();
    
}

Signal& Signal::copy( const Signal& other ) {
    
	clear();
    
    command = other.command;
    origin = other.origin; 
    
	for ( int i = 0; i < (int) other.args.size(); ++i ) {
        
		MessageArgType argType = other.getArgType( i );
		if ( argType == MESSAGE_TYPE_INT32 )
			args.push_back( new MessageArgInt32( other.getArgAsInt32( i ) ) );
        
		else if ( argType == MESSAGE_TYPE_FLOAT )
			args.push_back( new MessageArgFloat( other.getArgAsFloat( i ) ) );
        
		else if ( argType == MESSAGE_TYPE_STRING )
			args.push_back( new MessageArgString( other.getArgAsString( i ) ) );
        
		else {
			assert( false && "bad argument type" );
		}
        
	}
    
	return *this;
    
}


