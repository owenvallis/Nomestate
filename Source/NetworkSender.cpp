/*
 ==============================================================================
 
 NetworkSender.cpp
 Created: 10 Oct 2011 10:02:38pm
 Author:  Dimitri Diakopoulos
 
 ==============================================================================
 */

#include "NetworkSender.h"
#include "OSCMessage.h"
#include "PropertiesManager.h"

//forward declaration resolves the circular dependancy
class MessageCenter;

NetworkSender::NetworkSender()
{
    serverHostPort.referTo(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentHostPort", NULL));
    serverHostPort.addListener(this);
    
    setup("localhost", serverHostPort.getValue());
}

NetworkSender::~NetworkSender()
{
    serverHostPort.removeListener(this);
}

void NetworkSender::handleSignal(Signal s) 
{   

        OSCMessage oscMsg;
        
        if(s.getArgAsString(0) == "/nomestate/grid/led/set") {
            oscMsg.setAddress(s.getArgAsString(0));
            oscMsg.addIntArg(s.getArgAsInt32(1));
            oscMsg.addIntArg(s.getArgAsInt32(2));
            oscMsg.addIntArg(s.getArgAsInt32(3));
        } else if (s.getArgAsString(0) == "/nomestate/grid/led/all") {
            oscMsg.setAddress(s.getArgAsString(0)); 
            oscMsg.addIntArg(s.getArgAsInt32(1));
        } else if(s.getArgAsString(0) == "/nomestate/grid/led/color") {
            oscMsg.setAddress(s.getArgAsString(0));
            oscMsg.addIntArg(s.getArgAsInt32(1));
            oscMsg.addIntArg(s.getArgAsInt32(2));
            oscMsg.addIntArg(s.getArgAsInt32(3));
            oscMsg.addIntArg(s.getArgAsInt32(4));
            oscMsg.addIntArg(s.getArgAsInt32(5));
        } else if (s.getArgAsString(0) == "/sys/prefix"){
            DBG(s.getArgAsString(0) + " " + s.getArgAsString(1));
            oscMsg.setAddress(s.getArgAsString(0));
            oscMsg.addStringArg(s.getArgAsString(1));
        } else if (s.getArgAsString(0) == "/sys/info"){
            oscMsg.setAddress(s.getArgAsString(0));
            oscMsg.addIntArg(s.getArgAsInt32(1));
        }
        
        DBG("Sent OSC MSG:" + s.getArgAsString(0));
        
        sendMessage(oscMsg);
}

void NetworkSender::valueChanged(Value& value)
{
    if (value.refersToSameSourceAs (serverHostPort))
    {        
        DBG("setting host port: " + serverHostPort.getValue().toString());
        setup("localhost", serverHostPort.getValue());
        
        DBG("setting listen port: " + PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentListenPort", NULL).getValue().toString());
        OSCMessage oscMsg;        
        oscMsg.setAddress("/sys/port");
        oscMsg.addIntArg(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentListenPort", NULL).getValue());
        sendMessage(oscMsg);
        
        OSCMessage oscMsgB;        
        oscMsgB.setAddress("/sys/info");
        oscMsgB.addIntArg(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentListenPort", NULL).getValue());
        sendMessage(oscMsgB);
        
    }

}