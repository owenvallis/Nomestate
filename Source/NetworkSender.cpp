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
    
    rotation.referTo(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("rotation", NULL));
    rotation.addListener(this);
    
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
        } else if(s.getArgAsString(0) == "/nomestate/grid/led/color" && PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("currentdevice", NULL).toString().contains("chr")) {
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
    
    else if (value.refersToSameSourceAs(rotation))
    {
        DBG("Rotation: " + PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("rotation", NULL).getValue().toString());
        OSCMessage oscMsg;        
        oscMsg.setAddress("/sys/rotation");
        oscMsg.addIntArg(PropertiesManager::getInstance()->connectedDevices.getPropertyAsValue("rotation", NULL).getValue());
        sendMessage(oscMsg);
        
        for (int button = 0; button < 64; button++)
        {
            Colour currentColour = Colour::fromString(PropertiesManager::getInstance()->getButtonPropertyContainer(button)->propertyTree.getPropertyAsValue(Identifier("Colour"), NULL).toString());
            
            DBG("send color");
            
            OSCMessage oscMsgColor;
            
            oscMsgColor.setAddress("/nomestate/grid/led/color");
            // get the x position: LED bumber % 8
            oscMsgColor.addIntArg(button % 8);
            // get the y position: LED number / 8
            oscMsgColor.addIntArg(button / 8);
            // get the LED RED: 
            oscMsgColor.addIntArg(currentColour.getRed() >> 1);
            // get the LED GREEN: 
            oscMsgColor.addIntArg(currentColour.getGreen() >> 1);
            // get the LED BLUE: 
            oscMsgColor.addIntArg(currentColour.getBlue() >> 1);
            
            sendMessage(oscMsgColor); 
            
            OSCMessage oscMsgSet;
            
            oscMsgSet.setAddress("/nomestate/grid/led/set");
            // get the x position: LED bumber % 8
            oscMsgSet.addIntArg(button % 8);
            // get the y position: LED number / 8
            oscMsgSet.addIntArg(button / 8);
            // get the LED RED: 
            oscMsgSet.addIntArg(1);
            
            sendMessage(oscMsgSet); 
            
            PropertiesManager::getInstance()->getButtonPropertyContainer(button)->propertyTree.setProperty(Identifier("buttonState"), 1, NULL);
        }
    }

}