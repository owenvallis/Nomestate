/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic outline for a simple desktop window.

  ==============================================================================
*/

#include "MainWindow.h"
//#include "MainComponent.h"

//==============================================================================
MainAppWindow::MainAppWindow()
: DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                  Colours::black,
                  DocumentWindow::allButtons)
{
    commandManager = new ApplicationCommandManager();
    mainComponent = new MainComponent();
   
	setContentOwned (mainComponent, false);
    setMenuBar(mainComponent);
    
#if JUCE_MAC
    MenuBarModel::setMacMainMenu (mainComponent);
    setMenuBar (0);
#endif
    setUsingNativeTitleBar (true);
   
    setResizable (true, false);
	centreWithSize (650, 425);
    
    commandManager->registerAllCommandsForTarget(mainComponent);
    setVisible (true);


}


MainAppWindow::~MainAppWindow()
{
    
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
    MenuBarModel::setMacMainMenu (0);
#endif
}

void MainAppWindow::activeWindowStatusChanged(){
    if (isActiveWindow()) {
        DBG("Window focused and ready to update prefix");
        if (mainComponent != nullptr) {
            mainComponent->setSerialOscPrefix();
        }
    }
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
