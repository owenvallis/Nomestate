/*
  ==============================================================================

    MainComponent.cpp
    Created: 10 Oct 2011 10:55:11pm
    Author:  Dimitri Diakopoulos

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent() : propertyEditor(PropertiesManager::getInstance()->getPropertyGroupLibrary(), 
                                                PropertiesManager::getInstance()->getPropertyGroupFactory()),
                                 _sCore(_deviceManager),
                                 clearButton("clear")

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
        PropertiesManager::getInstance()->registerButton(button);
        buttonManager[i]->getColourValueObject().referTo ( PropertiesManager::getInstance()->getButtonPropertyContainer(i)->getGroupProperty(Identifier("Colour"),PropertyDescriptor(Identifier("Colour"), "Colour", Identifier("Colour")))); // this is ugly
        
        buttonManager[i]->getButtonModeValueObject().referTo ( PropertiesManager::getInstance()->getButtonPropertyContainer(i)->getGroupProperty(Identifier("ButtonMode"),PropertyDescriptor(Identifier("ButtonMode"), "ButtonMode", Identifier("ButtonMode")))); 
	}
    
    clearButton.addListener(this);
    
    addAndMakeVisible(&clearButton);
    addAndMakeVisible(&propertyEditor);
    	
    clearButton.setAlpha(0.1);
    
    commandManager = new ApplicationCommandManager();
    commandManager->registerAllCommandsForTarget(this);
    commandManager->registerAllCommandsForTarget(JUCEApplication::getInstance());

    commandManager->getKeyMappings()->resetToDefaultMappings();
    addKeyListener(commandManager->getKeyMappings());
    setApplicationCommandManagerToWatch(commandManager);
}


MainComponent::~MainComponent() {
    PropertiesManager::getInstance()->deregisterAllButtons();
}

void MainComponent::paint(Graphics& g) {
    g.setColour(Colour(25,25,25));
    g.fillRect(0, 0, getWidth(), getHeight());
}

void MainComponent::resized() {
    propertyEditor.setBounds(10,13,getWidth()/3, getHeight()-24);
    
    int buttonCounter = 0;
	int buttonAreaWidth = 250+(48*gridX);
	int buttonAreaHeight = 10+(48*gridY);
	
	for(int k=10; k<buttonAreaHeight; k+=48) {
		for (int i=250;i< buttonAreaWidth;i+=48) {
			buttonManager[buttonCounter]->setBounds(i,k,42,42);
			buttonCounter++;
		}		
	}
    
    clearButton.setBounds(250, 9 + (48*gridY), 87, 22);
}

const StringArray MainComponent::getMenuBarNames()
{
    const char* const names[] = { "File", 0 };
    
    return StringArray (names);
}

const PopupMenu MainComponent::getMenuForIndex (int menuIndex, const String& /*menuName*/)
{
    PopupMenu menu;
    
    if (menuIndex == 0) {
        menu.addCommandItem(commandManager, CommandIDs::save);
        menu.addCommandItem(commandManager, CommandIDs::open);
        menu.addCommandItem(commandManager, CommandIDs::preferences);
        menu.addSeparator();
        menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
    }
    
    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex){
}

void MainComponent::getAllCommands(Array<CommandID> &commands) {
    //JUCEApplication::getInstance()->getAllCommands(commands);
    commands.clear();
    
    const CommandID ids[] = { CommandIDs::save,
        CommandIDs::open,
        CommandIDs::preferences,
    };
    
    commands.addArray (ids, numElementsInArray (ids));
   
}

void MainComponent::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::save:
            result.setInfo ("Save...", "Saves a mapping configuration", CommandCategories::general, 0);
            result.addDefaultKeypress ('s', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::open:
            result.setInfo ("Open...", "Opens a mapping configuration", CommandCategories::general, 0);
            result.addDefaultKeypress ('o', ModifierKeys::commandModifier);
            break;
            
        case CommandIDs::preferences:
            result.setInfo ("Preferences...", "Shows the preferences panel.", CommandCategories::general, 0);
            result.addDefaultKeypress ('p', ModifierKeys::commandModifier);
            break;
            
        default:
            //JUCEApplication::getInstance()->getCommandInfo (commandID, result);
            break;
    }
}

bool MainComponent::perform(const InvocationInfo& info) {
    DBG("command performed");
    switch (info.commandID)
    {
        case CommandIDs::save:                  
            saveFile(); 
            break;
        case CommandIDs::open:                  
            loadFile(); 
            break;
        case CommandIDs::preferences:           
            openPreferences(); 
            break;
            
        //default: 
            //return perform (info);
    }
    
    return true;
}

void MainComponent::openPreferences() {

    PreferencesComponent preferencesWindow(_sCore, _deviceManager);
    DialogWindow::showModalDialog("Preferences", &preferencesWindow, this, Colours::black , true, false, false) ;
        
}

void MainComponent::loadFile(){
    FileChooser loadFile ("Please select a config file to load...",
                          File::getSpecialLocation (File::userDocumentsDirectory),
                          "*.conf", true);
    
    if (loadFile.browseForFileToOpen())
    {
        File configFile (loadFile.getResult());
        
        FileInputStream fileStream(configFile);
        
        ValueTree loadTree(ValueTree::readFromStream(fileStream));
                                
        for (int i =0; i<64; i++) {

            PropertiesManager::getInstance()->getButtonPropertyContainer(i)->propertyTree.setProperty("Colour", loadTree.getChild(i).getPropertyAsValue("Colour", NULL), NULL);
            PropertiesManager::getInstance()->getButtonPropertyContainer(i)->propertyTree.setProperty("Pressure", loadTree.getChild(i).getPropertyAsValue("Pressure", NULL), NULL);
            PropertiesManager::getInstance()->getButtonPropertyContainer(i)->propertyTree.setProperty("ButtonMode", loadTree.getChild(i).getPropertyAsValue("ButtonMode", NULL), NULL);
            PropertiesManager::getInstance()->getButtonPropertyContainer(i)->propertyTree.setProperty("buttonState", loadTree.getChild(i).getPropertyAsValue("buttonState", NULL), NULL); 

        }
    }
    
    clearButton.setInterceptsMouseClicks(true, false);
    clearButton.setAlpha(1.0);

}


void MainComponent::saveFile(){
    
    FileChooser saveFile ("Save config file ...",
                          File::getSpecialLocation (File::userDocumentsDirectory),
                          "*.conf", true);
    
    
    if (saveFile.browseForFileToSave(true))
    {
        File configFile (saveFile.getResult().getFullPathName() + ".conf");
        
        if (configFile.existsAsFile())
            configFile.deleteFile();
                
        FileOutputStream fileStream(configFile);
        
        ValueTree saveTree(Identifier("mainTree"));
        
        for (int i =0; i<64; i++) {
            saveTree.addChild(PropertiesManager::getInstance()->getButtonPropertyContainer(i)->propertyTree, i, nullptr);
        }
        
        saveTree.writeToStream(fileStream);
    }
    
}


void MainComponent::showProperties(){
    
    Array<int> buttonsBeingEdited;
    
    
    for (int i=0; i<buttonManager.size(); i++){
		if (buttonManager[i]->isBeingEdited()) {
			buttonsBeingEdited.add(buttonManager[i]->getButtonID());
            
            // reference counted Signal ( string command, string origin )
            Signal::SignalP ledStateSignal = new Signal("SEND_OSC", "MAINCOMPONENT");
            
            ledStateSignal->addStringArg("/nomestate/grid/led/set");
            // get the x position: LED bumber % 8
            ledStateSignal->addIntArg(i % 8);
            // get the y position: LED number / 8
            ledStateSignal->addIntArg(i / 8);
            // get the LED state: toggleState
            ledStateSignal->addIntArg(1);
            
            
            _sCore.getMessageCenter()->handleSignal(*ledStateSignal); 
		}
    }
    
    if(buttonsBeingEdited.size() > 0) {
        clearButton.setInterceptsMouseClicks(true, false);
        clearButton.setAlpha(1.0);
    }

    PropertiesManager::getInstance()->setButtonsBeingEdited(buttonsBeingEdited);
    propertyEditor.showPropertiesFor(PropertiesManager::getInstance()->getButtonsBeingEdited());
}

void MainComponent::setSerialOscPrefix() {
    DBG("setting prefix: /nomestate");

    Signal::SignalP prefixSignal = new Signal("SEND_OSC", "MAINCOMPONENT");
    prefixSignal->addStringArg("/sys/prefix");
    prefixSignal->addStringArg("/nomestate");
    _sCore.getMessageCenter()->handleSignal(*prefixSignal);
}

void MainComponent::changeListenerCallback (ChangeBroadcaster* objectThatHasChanged) {
    showProperties();
}

void MainComponent::buttonClicked (Button* buttonThatWasChanged) {
    
    if (buttonThatWasChanged == &clearButton) {
      
        selectedNomeButtonSet.deselectAll();
        
        for (int i =0; i < PropertiesManager::getInstance()->getButtonsBeingEdited().size(); i++) {
            buttonManager[dynamic_cast<ButtonPropertyContainer*>(PropertiesManager::getInstance()->getButtonsBeingEdited()[i])->getID()]->deselect();
            
        }
        
        // reference counted Signal ( string command, string origin )
        Signal::SignalP ledClearSignal = new Signal("SEND_OSC", "MAINCOMPONENT");
        
        ledClearSignal->addStringArg("/nomestate/grid/led/all");
        ledClearSignal->addIntArg(0);
        
        _sCore.getMessageCenter()->handleSignal(*ledClearSignal); 
        
        showProperties();
        
        clearButton.setInterceptsMouseClicks(false, false);
        clearButton.setAlpha(0.1);
    }
    
}

void MainComponent::mouseDown(const MouseEvent &e) {
    
    addChildComponent(&nomeButtonLasso);
    nomeButtonLasso.beginLasso(e, this);
    
}

void MainComponent::mouseDrag(const MouseEvent &e) {
   
    nomeButtonLasso.toFront(false);
    nomeButtonLasso.dragLasso(e);
}

void MainComponent::mouseUp (const MouseEvent &e) {
    for (int i = 0; i < selectedNomeButtonSet.getNumSelected(); i++) {
        selectedNomeButtonSet.getSelectedItem(i)->setBeingEdited(true);
    }
    showProperties();
    
    //std::cout << "numSelected: " << selectedNomeButtonSet.getNumSelected() << std::endl;
    
    nomeButtonLasso.endLasso();
    removeChildComponent(&nomeButtonLasso);
    
}



void MainComponent::findLassoItemsInArea (Array <NomeButton*>& results, const Rectangle<int>& area)
{
    results.clear();
    
    
    for (int i = 0; i<buttonManager.size(); i++)
    {
        buttonManager[i]->setBeingEdited(false);
        
        if (buttonManager[i]->getBounds().intersects(area)) {
            results.add(buttonManager[i]);
            buttonManager[i]->setBeingEdited(true);
        }
    }
}

SelectedItemSet <NomeButton*>& MainComponent::getLassoSelection()
{
    return selectedNomeButtonSet;
}



