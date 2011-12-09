/*
  ==============================================================================

    OSCArg.h
    Created: 14 Oct 2011 12:19:46am
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __OSCARG_H_B300C3D8__
#define __OSCARG_H_B300C3D8__

#include "../JuceLibraryCode/JuceHeader.h"

typedef enum OSCArgType
{
	OSC_TYPE_NONE,
	OSC_TYPE_INT32,
	OSC_TYPE_FLOAT,
	OSC_TYPE_STRING,
	OSC_TYPE_BLOB,
	OSC_TYPE_BUNDLE,
	OSC_TYPE_INDEXOUTOFBOUNDS
} SignalOSCArgType;


class OSCArg { 
    
public:
    
	OSCArg() {};
	virtual ~OSCArg() {};
    
	virtual SignalOSCArgType getType() { return OSC_TYPE_NONE; }
	virtual String getTypeName() { return "none"; }
    
};


#if defined TARGET_WIN32 && defined _MSC_VER
// required because MSVC isn't ANSI-C compliant
typedef long int32_t;
#endif

class SignalOSCArgInt32 : public OSCArg {
    
public:
	SignalOSCArgInt32( int32_t _value ) { value = _value; }
	~SignalOSCArgInt32() {};
    
	// return the type of this argument
	SignalOSCArgType getType() { return OSC_TYPE_INT32; }
	String getTypeName() { return "int32"; }
    
	// return value
	int32_t get() const { return value; }
	// set value
	void set( int32_t _value ) { value = _value; }
    
private:
	int32_t value;
    
};

class SignalOSCArgFloat : public OSCArg {
    
public:
	SignalOSCArgFloat( float _value ) { value = _value; }
	~SignalOSCArgFloat() {};
    
	// return the type of this argument
	SignalOSCArgType getType() { return OSC_TYPE_FLOAT; }
	String getTypeName() { return "float"; }
    
	// return value
	float get() const { return value; }
	// set value
	void set( float _value ) { value = _value; }
    
private:
    float value;
    
};

class SignalOSCArgString : public OSCArg {
    
public:
	SignalOSCArgString( String _value ) { value = _value; }
	~SignalOSCArgString() {};
    
	// return the type of this argument
	SignalOSCArgType getType() { return OSC_TYPE_STRING; }
	String getTypeName() { return "String"; }
    
	// return value
	String get() const { return value; }
	// set value
	void set( const char* _value ) { value = _value; }
    
private:
	String value;
    
};


#endif  // __OSCARG_H_B300C3D8__
