/*
 *  CustomLookAndFeel.h
 *  Nuance
 *
 *  Created by Jordan Hochenbaum on 2/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _CUSTLOOKANDFEEL_
#define _CUSTLOOKANDFEEL_

#include "../JuceLibraryCode/JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();
    
	void drawButtonBackground (Graphics& g,
							   Button& button,
							   const Colour& backgroundColour,
							   bool isMouseOverButton,
							   bool isButtonDown);
	
	
	//==========================================================================
	
private:
	const Colour createBaseColour (const Colour& buttonColour,
                                   const bool hasKeyboardFocus,
                                   const bool isMouseOverButton,
                                   const bool isButtonDown) throw();
	
	void drawToggleButton (Graphics& g, ToggleButton& button,
                           bool isMouseOverButton,
						   bool isButtonDown);
	
	void drawGlassLozenge (Graphics& g, const float x, const float y,
                           const float width, const float height,
                           const Colour& colour,
                           const float outlineThickness,
                           const float cornerSize,
                           const bool flatOnLeft,
                           const bool flatOnRight,
                           const bool flatOnTop,
                           const bool flatOnBottom) throw();
	
    
};

#endif // _CUSTLOOKANDFEEL_