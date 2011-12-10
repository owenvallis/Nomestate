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
#include "MidiIODeviceManager.h"
#include "PropertyGroup.h"
#include "NomeButton.h"
#include "PropertiesManager.h"
#include "SignalCore.h"
#include "PreferencesComponent.h"
#include "ZeroConfReceiver.h"
#include "ZeroConfResolve.h"



class MainComponent  :	public Component,
                        public MenuBarModel,
                        public ChangeListener,
                        public ButtonListener,
                        public LassoSource<NomeButton*>
{
	
public:
    
	MainComponent			();
	~MainComponent			();
	
	void paint				(Graphics& g);
	void resized			();
    
    void changeListenerCallback (ChangeBroadcaster* objectThatHasChanged);
    void buttonClicked (Button* buttonThatWasChanged);
    
    void configurePropertyEditor (PropertiesManager &pManager);
    void showProperties();
    
    void mouseDown (const MouseEvent &e); 
    void mouseUp (const MouseEvent &e); 
    void mouseDrag (const MouseEvent &e);
    
    void findLassoItemsInArea (Array <NomeButton*>& results, const Rectangle<int>& area);
    SelectedItemSet <NomeButton*>& getLassoSelection();
    
    const StringArray getMenuBarNames();
	const PopupMenu getMenuForIndex	(int topLevelMenuIndex, const String &menuName);
	void menuItemSelected	(int menuItemID, int topLevelMenuIndex);	
    
    void setSerialOscPrefix();
	
private:
    
    ZeroConfReceiver _ZeroConfReceiver;
    ZeroConfResolve  _ZeroConfResolve;
    
    void loadFile();
    void saveFile();
    void openPreferences();
    
    LassoComponent<NomeButton*>          nomeButtonLasso;    
    SelectedItemSet <NomeButton*>        selectedNomeButtonSet;
    
    MidiIODeviceManager					_deviceManager;
        
	PropertyGroupEditor                 propertyEditor;
    
    SignalCore                          _sCore;
        
	OwnedArray <NomeButton>				buttonManager;
    
    TextButton                          clearButton;
    String                              fileExtension;
    
	int									gridSize;
	int									gridX;
	int									gridY;
};



#endif  // __MAINCOMPONENT_H_39BE2997__
