/*
 *  CustomLookAndFeel.cpp
 *  Nuance
 *
 *  Created by Jordan Hochenbaum on 2/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel()
{
setColour(ComboBox::backgroundColourId, Colour(0xffe8e8e8) );
setColour(ComboBox::buttonColourId, Colours::grey );
setColour(ComboBox::arrowColourId, Colours::transparentBlack );
setColour(ComboBox::outlineColourId, Colour(0xff465366) );
setColour(TextButton::buttonColourId, Colour(0xff929da8) );
setColour(Slider::thumbColourId, Colours::yellow);
setColour(Slider::backgroundColourId, Colours::white);
setColour(Slider::textBoxTextColourId, Colours::black);
setColour(PopupMenu::backgroundColourId, Colour(0xffe8e8e8) );
setColour(TextEditor::outlineColourId, Colours::lightgrey);
setColour(TextEditor::focusedOutlineColourId, Colours::transparentBlack);	
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::drawButtonBackground (Graphics& g,
											   Button& button,
											   const Colour& backgroundColour,
											   bool isMouseOverButton,
											   bool isButtonDown)
{
    const int width = button.getWidth();
    const int height = button.getHeight();
	
	
	const Colour baseColour (createBaseColour (backgroundColour,
                                               button.hasKeyboardFocus (true),
                                               isMouseOverButton, isButtonDown)
							 .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
	
    drawGlassLozenge (g,
                      0,
                      0,
                      width,
                      height,
                      baseColour, 0.1f, -1.0f,
                      button.isConnectedOnLeft(),
                      button.isConnectedOnRight(),
                      button.isConnectedOnTop(),
                      button.isConnectedOnBottom());
}

const Colour CustomLookAndFeel::createBaseColour (const Colour& buttonColour,
												   const bool hasKeyboardFocus,
												   const bool isMouseOverButton,
												   const bool isButtonDown) throw()
{	
	const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
	const Colour baseColour (buttonColour.withMultipliedSaturation (sat));
	const Colour baseDownColour(0xffeaf20e);
	
	if (isButtonDown)
		return baseDownColour;
	else if (isMouseOverButton)
		return baseColour.contrasting (0.1f);
	
	return baseColour;
}

void CustomLookAndFeel::drawToggleButton (Graphics& g,
                                           ToggleButton& button,
                                           bool isMouseOverButton,
                                           bool isButtonDown)
{
    if (button.hasKeyboardFocus (true))
    {
        g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
        g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }
	
	const int width = button.getWidth();
    const int height = button.getHeight();
	
	//draw button 	
	g.setColour (button.getToggleState() ?  
				 Colour(0xffeaf20e)
				 : Colour(0xff929da8) );
	g.fillRect (0, 0, width, height);
	
	//draw outline
	g.setColour (Colour(0xff465366) );
	g.drawRect (0, 0, width, height, 1);
	
	g.setColour(Colours::black );
	
	g.drawFittedText (button.getButtonText(),
                      0, 0,
                      width, height,
                      Justification::centred, 10);
	
}

void CustomLookAndFeel::drawGlassLozenge (Graphics& g,
                                           const float x, const float y,
                                           const float width, const float height,
                                           const Colour& colour,
                                           const float outlineThickness,
                                           const float cornerSize,
                                           const bool flatOnLeft,
                                           const bool flatOnRight,
                                           const bool flatOnTop,
                                           const bool flatOnBottom) throw()
{
    if (width <= outlineThickness || height <= outlineThickness)
        return;
	
    const int intX = (int) x;
    const int intY = (int) y;
    const int intW = (int) width;
    const int intH = (int) height;
    
	//draw button 	
	g.setColour (colour );
	g.fillRect (intX, intY, intW, intH);
	
	g.setColour (Colour(0xff465366) );
	g.drawRect (intX, intY, intW, intH, 1);	
}

void CustomLookAndFeel::drawPropertyComponentLabel	(Graphics& g, int width, int height,
                                                     PropertyComponent& component)
{
    g.setColour(Colour(81,81,81));
    g.fillAll();
}
