/*
  ==============================================================================

    Message.cpp
    Created: 30 Oct 2011 6:34:29pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "Message.h"
#include <iostream>
#include <assert.h>

Msg::Msg() { }

Msg::~Msg(){
	clear();
}

void Msg::clear() {
    
	for ( unsigned int i=0; i<args.size(); ++i )
		delete args[i];
    
	args.clear();
    
}

int Msg::getNumArgs() const {
    
	return (int) args.size();
    
}

MessageArgType Msg::getArgType( int index ) const {
    
    if ( index >= (int) args.size() ) {
        fprintf(stderr,"Msg::getArgType: index %d out of bounds\n", index );
        return MESSAGE_TYPE_INDEXOUTOFBOUNDS;
    }
    else
        return args[index]->getType();
    
}

String Msg::getArgTypeName( int index ) const {
    
    if ( index >= (int)args.size() ) {
        fprintf(stderr,"Msg::getArgTypeName: index %d out of bounds\n", index );
        return "INDEX OUT OF BOUNDS";
    }
    
    else
        return args[index]->getTypeName();
    
}

int32_t Msg::getArgAsInt32( int index ) const {
    
	if ( getArgType(index) != MESSAGE_TYPE_INT32 ) {
	    if ( getArgType( index ) == MESSAGE_TYPE_FLOAT ) {
            fprintf(stderr, "Message:getArgAsInt32: warning: converting int32 to float for argument %i\n", index );
            return ((MessageArgFloat*)args[index])->get();
        }
        
        else {
            fprintf(stderr, "Message:getArgAsInt32: error: argument %i is not a number\n", index );
            return 0;
        }
	}
	else
        return ((MessageArgInt32*)args[index])->get();
    
}


float Msg::getArgAsFloat( int index ) const {
    
	if ( getArgType(index) != MESSAGE_TYPE_FLOAT ) {
	    if ( getArgType( index ) == MESSAGE_TYPE_INT32 ) {
            fprintf(stderr, "Message:getArgAsFloat: warning: converting float to int32 for argument %i\n", index );
            return ((MessageArgInt32*)args[index])->get();
        }
        
        else {
            fprintf(stderr, "Message:getArgAsFloat: error: argument %i is not a number\n", index );
            return 0;
        }
	}
	else
        return ((MessageArgFloat*)args[index])->get();
    
}


String Msg::getArgAsString( int index ) const {
    
    if ( getArgType(index) != MESSAGE_TYPE_STRING ) {
        
	    if ( getArgType( index ) == MESSAGE_TYPE_FLOAT ) {
            char buf[1024];
            sprintf(buf,"%f",((MessageArgFloat*)args[index])->get() );
            fprintf(stderr, "Message:getArgAsString: warning: converting float to string for argument %i\n", index );
            return buf;
        }
        
	    else if ( getArgType( index ) == MESSAGE_TYPE_INT32 ) {
            char buf[1024];
            sprintf(buf,"%i",((MessageArgInt32*)args[index])->get() );
            fprintf(stderr, "Message:getArgAsString: warning: converting int32 to string for argument %i\n", index );
            return buf;
        }
        
        else {
            fprintf(stderr, "Message:getArgAsString: error: argument %i is not a string\n", index );
            return "";
        }
        
	}
    
	else
        return ((MessageArgString*)args[index])->get();
    
}

void Msg::addIntArg( int32_t argument ) {
	args.push_back( new MessageArgInt32( argument ) );
}

void Msg::addFloatArg( float argument ) {
	args.push_back( new MessageArgFloat( argument ) );
}

void Msg::addStringArg( String argument ) {
	args.push_back( new MessageArgString( argument ) );
}


Msg& Msg::copy( const Msg& other ) {
    
	clear();
    
	// copy arguments
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