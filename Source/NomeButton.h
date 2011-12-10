/*
  ==============================================================================

    NomeButton.h
    Created: 6 Nov 2011 3:47:16am
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __NOMEBUTTON_H_630E4EFB__
#define __NOMEBUTTON_H_630E4EFB__

#include "../JuceLibraryCode/JuceHeader.h"

class NomeButton : public Component,
                   public ChangeBroadcaster,
                   public ValueListener
{
public:
    NomeButton();
    ~NomeButton();
    
    void    paint (Graphics& g);
	void    resized();
        
    void    setButtonID(int buttonID) { _buttonID = buttonID;}
    int     getButtonID() { return _buttonID; }
    
    Value&  getColourValueObject() { return buttonColour; }  
    Value&  getButtonModeValueObject() { return buttonMode; }
    void    valueChanged(Value& value);
	
	bool	isBeingEdited();
    void    setBeingEdited(bool beingEdited);
	
	void	mouseMove (const MouseEvent &e);
	void	mouseEnter (const MouseEvent &e);
	void	mouseExit (const MouseEvent &e);
	void	mouseDown (const MouseEvent &e);
	void	mouseUp (const MouseEvent &e);
    
    void    deselect();
    
private:
    int         _buttonID;
    Value		buttonColour;
    Value       buttonMode;
	bool		isHovered;
	bool		isSelected;
    Label       buttonModeLabel;

};


#endif  // __NOMEBUTTON_H_630E4EFB__
