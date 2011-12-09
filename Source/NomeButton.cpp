/*
  ==============================================================================

    NomeButton.cpp
    Created: 6 Nov 2011 3:47:16am
    Author:  Owen Vallis

  ==============================================================================
*/

#include "NomeButton.h"

NomeButton::NomeButton()
{
	isHovered = false;
	isSelected = false;
	
	buttonColour.addListener(this);
}

NomeButton::~NomeButton()
{
    buttonColour.removeListener(this);
}

void NomeButton::paint(Graphics& g)
{
    g.setColour(Colour::fromString(buttonColour.toString()));
    
    if (isHovered || isSelected){
		g.fillRoundedRectangle(0,0,40,40,8);
	} else {	
        g.fillRoundedRectangle(2, 2, 36, 36, 6);
    }
}

void NomeButton::resized()
{
    
}

void NomeButton::valueChanged(Value& value)
{
    if (value.refersToSameSourceAs (buttonColour))
    {
        repaint();
    }
}
//------Property Groups-------------------------------------------------------------------------------------//


bool NomeButton::isBeingEdited(){
    return isSelected;	
}

void NomeButton::setBeingEdited(bool beingEdited) {
    isSelected = beingEdited;
    repaint();
}

void NomeButton::deselect() { 
    isSelected = false; 
	repaint();
} 


//------mouse callbacks-------------------------------------------------------------------------------------//
void NomeButton::mouseMove (const MouseEvent &e){
	isHovered = true;
	repaint();
}
void NomeButton::mouseEnter (const MouseEvent &e){
	isHovered = true;
	DBG("mouse entered " + String(_buttonID));
	repaint();
}
void NomeButton::mouseExit (const MouseEvent &e){
	isHovered = false;
	repaint();
	
}
void NomeButton::mouseDown (const MouseEvent &e){
	repaint();
}

void NomeButton::mouseUp (const MouseEvent &e){
	
    isSelected = !isSelected;
	if(isSelected){
		DBG("mouse selected " + String(_buttonID));
	}else{
		DBG("mouse deselected " + String(_buttonID));
	}
	isHovered = false;
	sendChangeMessage();
	repaint();
}
