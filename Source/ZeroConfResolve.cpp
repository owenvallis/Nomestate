/*
  ==============================================================================

    ZeroConfResolve.cpp
    Created: 8 Dec 2011 11:18:34pm
    Author:  Owen Vallis

  ==============================================================================
*/

#include "ZeroConfResolve.h"

ZeroConfResolve::ZeroConfResolve() : Thread ("ZerconfResolve Thread")
{    
    currentDevice.referTo(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL));
    currentDevice.addListener(this);
}

ZeroConfResolve::~ZeroConfResolve()
{       
    // allow the thread 2 seconds to stop cleanly - should be plenty of time.
    stopThread (2000);
}

void ZeroConfResolve::run()
{
    DNSServiceRef  serviceRef;
    DNSServiceErrorType err;
    fd_set descriptors;
    int sockfd;
    int selRes;
    
    String deviceName = String(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL).toString()).removeCharacters ("\"#@,;:<>*^|?\\/() "); 

    
    // Launch the resolution procedure.
    err = DNSServiceResolve(&serviceRef,
                            0,
                            0,
                            PropertiesManager::getInstance()->connectedDevices.getChildWithName(Identifier(deviceName)).getPropertyAsValue(Identifier("deviceName"), NULL).toString().toUTF8(),
                            PropertiesManager::getInstance()->connectedDevices.getChildWithName(Identifier(deviceName)).getPropertyAsValue(Identifier("regType"), NULL).toString().toUTF8(),
                           PropertiesManager::getInstance()->connectedDevices.getChildWithName(Identifier(deviceName)).getPropertyAsValue(Identifier("domain"), NULL).toString().toUTF8(),
                            ResolveReply,
                            NULL);
    
    // Check for errors
    if (err != kDNSServiceErr_NoError) {
        DBG("ChronomeState " + String(err) + " start the resolution procedure");
        return;
    }
    
    // Wait for the callback. CAUTION: this call is blocking and may stuck you
    // thread. This will call the callback function.
    sockfd = DNSServiceRefSockFD(serviceRef);
        
    // Set the fd_set to start select()
    FD_ZERO(&descriptors);
    FD_SET(sockfd, &descriptors);
    
    selRes = select(sockfd + 1, &descriptors, NULL, NULL, NULL);
    
    
    // Wait for the response.
    if (selRes > 0) {
        err = DNSServiceProcessResult(serviceRef);
        // Cancel the resolution process since we must have the data yet.
        DNSServiceRefDeallocate(serviceRef);
        if (err != kDNSServiceErr_NoError) {
            DBG("ChronomeState " + String(err) + " process the resolution procedure");
            return;
        }
    } else {
        DBG("ChronomeState " + String(err) + " wait to the resolution response");
        return;
    }
}

void ZeroConfResolve::ResolveReply(DNSServiceRef ref, DNSServiceFlags flags,
                                    uint32_t interfaceIndex, DNSServiceErrorType error,
                                    const char * fullname, const char * hostname,
                                    uint16_t port, uint16_t txtLen,
                                    const unsigned char * txtVal, void * context)
{
    if (error != kDNSServiceErr_NoError) {
        DBG("OucBonjour " + String(error) + " complete the resolve callback");
        return;
    }

    int serverHostPort = ntohs(port);
    
    // Copy the information of resolution results to the node.
    DBG("RESOLVED: " + String(fullname) + " at " + String(hostname) + ": " + String(serverHostPort));

    PropertiesManager::getInstance()->connectedDevices.setProperty(Identifier("currentHostPort"), serverHostPort, NULL);
    
}

void ZeroConfResolve::valueChanged(Value& value)
{
    if (value.refersToSameSourceAs (currentDevice))
    {
        DBG("let's grab the server port");
        
        startThread();

    }
}