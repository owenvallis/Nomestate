/*
  ==============================================================================

    NetworkSender.cpp
    Created: 10 Oct 2011 10:02:38pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "NetworkSender.h"

//forward declaration resolves the circular dependancy
class MessageCenter;

NetworkSender::NetworkSender()
{
    
}

NetworkSender::~NetworkSender()
{
    
}

void NetworkSender::handleSignal(Signal s) 
{   
    DBG("Bang");
}