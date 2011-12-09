/*
  ==============================================================================

    ZeroConfReceiver.h
    Created: 6 Dec 2011 1:54:54pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __ZEROCONFRECEIVER_H_EE257A72__
#define __ZEROCONFRECEIVER_H_EE257A72__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PropertiesManager.h"
#include <dns_sd.h>

class ZeroConfReceiver : public Thread
{
public: 
    ZeroConfReceiver();
    ~ZeroConfReceiver();
    
    void run();
    
private:
	DNSServiceRef  serviceRef;
   
    
    static void MyBrowseCallBack(DNSServiceRef service,
                                    DNSServiceFlags flags,
                                    uint32_t interfaceIndex,
                                    DNSServiceErrorType errorCode,
                                    const char * name,
                                    const char * type,
                                    const char * domain,
                                    void * context);
};


#endif  // __ZEROCONFRECEIVER_H_EE257A72__
