/*
  ==============================================================================

    OSCBundle.h
    Created: 13 Oct 2011 11:56:54pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __OSCBUNDLE_H_DB889FF4__
#define __OSCBUNDLE_H_DB889FF4__

#include <vector>
#include "OSCMessage.h"

class OSCBundle {
    
public:	
	OSCBundle();
	~OSCBundle();
	OSCBundle( const OSCBundle& other ) { copy ( other ); }
	OSCBundle& operator= ( const OSCBundle& other ) { return copy( other ); }
	/// for operator= and copy constructor
	OSCBundle& copy( const OSCBundle& other );
	
	/// erase contents
	void clear() { messages.clear(); bundles.clear(); }
    
	/// add bundle elements
	void addBundle( const OSCBundle& element );
	void addMessage( const OSCMessage& message );
	
	/// get bundle elements
	int getBundleCount() const { return bundles.size(); }
	int getMessageCount() const { return messages.size(); }
	/// return the bundle or message at the given index
	OSCBundle& getBundleAt( int i ) { return bundles[i]; }
	OSCMessage& getMessageAt( int i ) { return messages[i]; }
	
private:
    
	std::vector< OSCMessage > messages;
	std::vector< OSCBundle > bundles;
    
};

#endif  // __OSCBUNDLE_H_DB889FF4__
