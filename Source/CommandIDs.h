/*
  ==============================================================================

    GuiKeyCommands.h
    Created: 11 Dec 2011 1:42:21pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef __GUIKEYCOMMANDS_H_8B9EC661__
#define __GUIKEYCOMMANDS_H_8B9EC661__


/**
 A namespace to hold all the possible command IDs.
 */
namespace CommandIDs
{
    static const int save             = 0x200010;
    static const int open             = 0x200020;
    static const int preferences      = 0x200030;
}

namespace CommandCategories
{
    static const char* const general       = "General";
}


#endif  // __GUIKEYCOMMANDS_H_8B9EC661__
