/*
  ==============================================================================

    MainComponent.h
    Created: 10 Oct 2011 10:55:11pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#ifndef __MAINCOMPONENT_H_39BE2997__
#define __MAINCOMPONENT_H_39BE2997__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PropertyGroup.h"
#include "NomeButton.h"
#include "PropertiesManager.h"
#include "SignalCore.h"

class MainComponent  :	public Component,
                        public ChangeListener 
{
	
public:
    
	MainComponent			();
	~MainComponent			();
	
	void paint				(Graphics& g);
	void resized			();
    
    void changeListenerCallback (ChangeBroadcaster* objectThatHasChanged);
    void configurePropertyEditor(PropertiesManager &pManager);
	
private:
        
    
    SignalCore                          _sCore;

    PropertiesManager                   _pManager;
    
	PropertyGroupEditor                 propertyEditor;
    
	OwnedArray <NomeButton>				buttonManager;
    
	int									gridSize;
	int									gridX;
	int									gridY;
};



#endif  // __MAINCOMPONENT_H_39BE2997__
