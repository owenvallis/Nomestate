/*
 ==============================================================================
 
 MessageArg.h
 Created: 14 Oct 2011 12:19:46am
 Author:  Dimitri Diakopoulos
 
 ==============================================================================
 */

#ifndef __MessageArg_H_B300C3D8__
#define __MessageArg_H_B300C3D8__

#include "../JuceLibraryCode/JuceHeader.h"

typedef enum MsgArgType {
	MESSAGE_TYPE_NONE,
	MESSAGE_TYPE_INT32,
	MESSAGE_TYPE_FLOAT,
	MESSAGE_TYPE_STRING,
	MESSAGE_TYPE_BLOB,
	MESSAGE_TYPE_BUNDLE,
	MESSAGE_TYPE_INDEXOUTOFBOUNDS
} MessageArgType;

class MessageArg { 
    
public:
    
	MessageArg() {};
	virtual ~MessageArg() {};
    
	virtual MessageArgType getType() { return MESSAGE_TYPE_NONE; }
	virtual String getTypeName() { return "none"; }
    
};


#if defined TARGET_WIN32 && defined _MSC_VER
    // required because MSVC isn't ANSI-C compliant
    typedef long int32_t;
#endif

class MessageArgInt32 : public MessageArg {
    
public:
	MessageArgInt32( int32_t _value ) { value = _value; }
	~MessageArgInt32() {};
    
	// return the type of this argument
	MessageArgType getType() { return MESSAGE_TYPE_INT32; }
	String getTypeName() { return "int32"; }
    
	// return value
	int32_t get() const { return value; }
	// set value
	void set( int32_t _value ) { value = _value; }
    
private:
	int32_t value;
    
};

class MessageArgFloat : public MessageArg {
    
public:
	MessageArgFloat( float _value ) { value = _value; }
	~MessageArgFloat() {};
    
	// return the type of this argument
	MessageArgType getType() { return MESSAGE_TYPE_FLOAT; }
	String getTypeName() { return "float"; }
    
	// return value
	float get() const { return value; }
	// set value
	void set( float _value ) { value = _value; }
    
private:
    float value;
    
};

class MessageArgString : public MessageArg {
    
public:
	MessageArgString( String _value ) { value = _value; }
	~MessageArgString() {};
    
	// return the type of this argument
	MessageArgType getType() { return MESSAGE_TYPE_STRING; }
	String getTypeName() { return "String"; }
    
	// return value
	String get() const { return value; }
	// set value
	void set( const char* _value ) { value = _value; }
    
private:
	String value;
    
};


#endif  // __MessageArg_H_B300C3D8__
