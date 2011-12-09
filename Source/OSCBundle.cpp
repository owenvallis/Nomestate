/*
  ==============================================================================

    OSCBundle.cpp
    Created: 13 Oct 2011 11:56:54pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "OSCBundle.h"

OSCBundle::OSCBundle() { }

OSCBundle::~OSCBundle(){ }

OSCBundle& OSCBundle::copy( const OSCBundle& other ) {
    
	for ( int i=0; i<(int)other.bundles.size(); i++ ) {
		bundles.push_back( other.bundles[i] );
	}
    
	for ( int i=0; i<(int)other.messages.size(); i++ ) {
		messages.push_back( other.messages[i] );
	}
    
	return *this;
    
}

void OSCBundle::addBundle( const OSCBundle& bundle ) {
	bundles.push_back( bundle );
}

void OSCBundle::addMessage( const OSCMessage& message ){
	messages.push_back( message );
}