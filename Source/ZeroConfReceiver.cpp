/*
 ==============================================================================
 
 ZeroConfReceiver.cpp
 Created: 6 Dec 2011 1:54:54pm
 Author:  Owen Vallis
 
 ==============================================================================
 */

#include "ZeroConfReceiver.h"

ZeroConfReceiver::ZeroConfReceiver() : Thread ("Zerconf Thread"),
                                       serviceRef(NULL)
{    
    startThread();
}

ZeroConfReceiver::~ZeroConfReceiver()
{   
    DNSServiceRefDeallocate(serviceRef);
    // allow the thread 2 seconds to stop cleanly - should be plenty of time.
    stopThread (2000);
}

void ZeroConfReceiver::run()
{
    DNSServiceErrorType error;
    int sockfd;
    int selRes;
    fd_set descriptors;
    
	error = DNSServiceBrowse(&serviceRef,
                             0,                // no flags
                             0,                // all network interfaces
                             "_monome-osc._udp",     // service type
                             "",               // default domains
                             MyBrowseCallBack, // call back function
                             NULL);            // no context
    
        
    // If there are no errors, launch the event loop.
    if (error != kDNSServiceErr_NoError) {
        DBG("ChronomeState: " + String(error) + " launch the discovery process");
        return; // Thread ends.
    }
    
    sockfd = DNSServiceRefSockFD(serviceRef);
        
    // threadShouldExit() returns true when the stopThread() method has been
    // called, so we should check it often, and exit as soon as it gets flagged.
    while (! threadShouldExit())
    {   
        // Set the fd_set to start select()
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);
        
        // Wait until there is something to do
        selRes = select(sockfd + 1, &descriptors, NULL, NULL, NULL);
        
        // Process the new result.
        if (selRes > 0) {
            if (FD_ISSET(sockfd, &descriptors)) {
                // This function will call the appropiate callback to process the
                // event, in this case the BrowseReply static method.
                error = DNSServiceProcessResult(serviceRef);
                if (error != kDNSServiceErr_NoError) {
                    DBG("ChronomeState: " + String(error) + " process an event in event loop");
                    return;
                }
            }
        } else if (selRes == -1) {
            DBG("ChronomeState: The select() call failed");
            return;
        }
    }
    
}

void ZeroConfReceiver::MyBrowseCallBack(DNSServiceRef service,
                                        DNSServiceFlags flags,
                                        uint32_t interfaceIndex,
                                        DNSServiceErrorType errorCode,
                                        const char * name,
                                        const char * type,
                                        const char * domain,
                                        void * context)
{
	if (errorCode != kDNSServiceErr_NoError) 
    {
		DBG("MyBrowseCallBack returned " + String(errorCode));  
        return;
    }
    
	else
    {
        
        // if we are finished receiving data
        if (!(flags & kDNSServiceFlagsMoreComing)) 
        {
            String deviceName = String(name).removeCharacters ("\"#@,;:<>*^|?\\/() "); 
            DBG(deviceName);

            // if this is an add 
            if(flags & kDNSServiceFlagsAdd) 
            {
                PropertiesManager::getInstance()->connectedDevices.getOrCreateChildWithName(Identifier(deviceName), NULL).setProperty(Identifier("deviceName"), name, NULL);
                PropertiesManager::getInstance()->connectedDevices.getOrCreateChildWithName(Identifier(deviceName), NULL).setProperty(Identifier("regType"), type, NULL);
                PropertiesManager::getInstance()->connectedDevices.getOrCreateChildWithName(Identifier(deviceName), NULL).setProperty(Identifier("domain"), domain, NULL);
                DBG("added " + PropertiesManager::getInstance()->connectedDevices.getChildWithName(Identifier(deviceName)).getPropertyAsValue(Identifier(String("deviceName")), NULL).toString());
            }
            else
            {
                if(PropertiesManager::getInstance()->connectedDevices.getChildWithName(Identifier(deviceName)).isValid())
                {
                    PropertiesManager::getInstance()->connectedDevices.removeChild(PropertiesManager::getInstance()->connectedDevices.getChildWithName(Identifier(deviceName)), NULL);
                    DBG("removed " + deviceName);
                }                   
            }
        }

    }
	if (!(flags & kDNSServiceFlagsMoreComing)) fflush(stdout);    
}









