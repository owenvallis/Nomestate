/*
  ==============================================================================

    AbletonStyleOSCComponent.h
    Created: 5 Dec 2011 12:16:23pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __ABLETONSTYLEOSCCOMPONENT_H_3A13D744__
#define __ABLETONSTYLEOSCCOMPONENT_H_3A13D744__

#include "../../JuceLibraryCode/JuceHeader.h"

class AbletonStyleOSCComponent  : public Component,
                                 public ButtonListener
{
public:
    //==============================================================================
    AbletonStyleOSCComponent ();
    ~AbletonStyleOSCComponent();
	
    //==============================================================================
	
    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);	
	
private:
    TextButton      setOSCPrefix;
    
};





#endif  // __ABLETONSTYLEOSCCOMPONENT_H_3A13D744__
