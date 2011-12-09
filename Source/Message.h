/*
  ==============================================================================

    Msg.h
    Created: 30 Oct 2011 6:34:29pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __Msg_H_5825CC7A__
#define __Msg_H_5825CC7A__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MessageArg.h"
#include <vector>
    
using namespace std;

class Msg {
    
public:
    
    Msg();
    virtual ~Msg();
    
    Msg(const Msg& other){ 
        copy ( other ); 
    }
    
    Msg& operator= ( const Msg& other ) { 
        return copy( other ); 
    }
    
    // for operator= and copy constructor
    virtual Msg& copy( const Msg& other );
    
    // clear this Msg, erase all contents
    virtual void clear();
    
    // return number of arguments
    int getNumArgs() const;
    // return argument type code for argument # index
    MessageArgType getArgType( int index ) const;
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
    
    void addIntArg( int32_t argument );
    void addFloatArg( float argument );
    void addStringArg( String argument );
    
protected:
    
    String address;
    
    vector<MessageArg*> args;
    
    String remote_host;
    int remote_port;
    
};

#endif  // __Msg_H_5825CC7A__
