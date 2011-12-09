/*
  ==============================================================================

    MainComponent.cpp
    Created: 10 Oct 2011 10:55:11pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent() : propertyEditor(_pManager.getPropertyGroupLibrary(), _pManager.getPropertyGroupFactory())

{
	//setup default grid size
	gridX = 8;
	gridY = 8;
	gridSize = gridX * gridY;
	
	
	//add 64 buttons
	for (int i=0; i<gridSize; i++)
	{
		NomeButton* button;
		addAndMakeVisible(button = new NomeButton());
		button->setButtonID(i);
		button->addChangeListener(this);
		buttonManager.add(button);
        _pManager.registerButton(button);
        buttonManager[i]->getValueObject().referTo ( _pManager.getButtonPropertyContainer(i)->getGroupProperty(Identifier("Colour"),PropertyDescriptor(Identifier("Colour"), "Colour", Identifier("Colour"))));
	}
    
    _sCore.getsignalModifier()->setModel(_pManager);
    
    addAndMakeVisible(&propertyEditor);
    	
}


MainComponent::~MainComponent() {
    _pManager.deregisterAllButtons();
}

void MainComponent::paint(Graphics& g) {
    g.setColour(Colour(25,25,25));
    g.fillRect(0, 0, getWidth(), getHeight());
}

void MainComponent::resized() {
    
    propertyEditor.setBounds(10,13,getWidth()/3, getHeight()-25);
    
    int buttonCounter = 0;
	int buttonAreaWidth = 250+(48*gridX);
	int buttonAreaHeight = 10+(48*gridY);
	
	for(int k=10; k<buttonAreaHeight; k+=48) {
		for (int i=250;i< buttonAreaWidth;i+=48) {
			buttonManager[buttonCounter]->setBounds(i,k,42,42);
			std::cout << buttonCounter << std::endl;
			buttonCounter++;
		}		
	}
}

void MainComponent::changeListenerCallback (ChangeBroadcaster* objectThatHasChanged) {
    Array<int> buttonsBeingEdited;
    
    for (int i=0; i<buttonManager.size(); i++){
		if (buttonManager[i]->isBeingEdited()) {
			buttonsBeingEdited.add(buttonManager[i]->getButtonID());
		}
    }
    _pManager.setButtonsBeingEdited(buttonsBeingEdited);
    propertyEditor.showPropertiesFor(_pManager.getButtonsBeingEdited());
}

