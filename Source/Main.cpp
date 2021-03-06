/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "CustomLookAndFeel.h"

ApplicationProperties* appProperties = nullptr;

//==============================================================================
class NomeStateApplication  : public JUCEApplication
{
public:
    //==============================================================================
    NomeStateApplication()
    {
    }

    ~NomeStateApplication()
    {
    }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        
        // initialise our settings file..
        
        PropertiesFile::Options options;
        options.applicationName     = "Nomestate";
        options.filenameSuffix      = "settings";
        options.folderName          = "Nomestate";
        options.osxLibrarySubFolder = "Application Support";
        
        appProperties = new ApplicationProperties();
        appProperties->setStorageParameters (options);
        
        LookAndFeel::setDefaultLookAndFeel (&customLookAndFeel);
        // Do your application's initialisation code here..
        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        // Do your application's shutdown code here..
        mainWindow = 0;
        appProperties->closeFiles();
        
        deleteAndZero (appProperties);
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    
    const String getApplicationName()
    {
        return "Nomestate";
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return false;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        
    }
    
private:
    ScopedPointer <MainAppWindow> mainWindow;
    CustomLookAndFeel customLookAndFeel;
    
};

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(NomeStateApplication)
