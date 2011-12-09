/*
  ==============================================================================

    ZeroConfResolve.h
    Created: 8 Dec 2011 11:18:34pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __ZEROCONFRESOLVE_H_253C857D__
#define __ZEROCONFRESOLVE_H_253C857D__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PropertiesManager.h"
#include <dns_sd.h>

class ZeroConfResolve : public Thread,
                        public ValueListener
{
public: 
    ZeroConfResolve();
    ~ZeroConfResolve();
    
    void run();
    void valueChanged(Value& value);
    
private:
    Value currentDevice;
    
    
    static void ResolveReply(DNSServiceRef ref,
                             DNSServiceFlags flags,
                             uint32_t interfaceIndex,
                             DNSServiceErrorType error,
                             const char * fullname,
                             const char * hostname,
                             uint16_t port,
                             uint16_t txtLen,
                             const unsigned char * txtVal,
                             void * context);
    
};



#endif  // __ZEROCONFRESOLVE_H_253C857D__
