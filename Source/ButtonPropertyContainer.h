/*
  ==============================================================================

    ButtonPropertyContainer.h
    Created: 6 Nov 2011 11:08:26pm
    Author:  Owen Vallis

  ==============================================================================
*/

#ifndef __BUTTONPROPERTYCONTAINER_H_B84412B7__
#define __BUTTONPROPERTYCONTAINER_H_B84412B7__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PropertyGroup.h"

class ButtonPropertyContainer : public PropertyGroup::Container
{     
    
public:
    ButtonPropertyContainer(int ButtonPropertyContainerID) : propertyTree(Identifier(String(ButtonPropertyContainerID)))
    {
        propertyTree.setProperty("ButtonMode", 0, 0);
        propertyTree.setProperty("Pressure", 0, 0);
        propertyTree.setProperty("Colour", 0, 0);
        propertyTree.setProperty("buttonState", 0,0);
        propertyTree.getPropertyAsValue("Colour", NULL) = Colour(55,55,55).toString();
        
        _id = ButtonPropertyContainerID;
    };
    
    ~ButtonPropertyContainer() {};
    
    void    getPropertyGroups (PropertyGroup::IdList& groupIds)
    {
        //groupIds.add("mainGroup");
        groupIds.add("nomeGroup");
        groupIds.add("chronomeGroup");
    }
    
    
	Value	getGroupProperty (const Identifier& groupId, const PropertyDescriptor& propInfo)
    {
            return propertyTree.getPropertyAsValue(propInfo.getLabel(), NULL);	
    }

	void	valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
    {
        
    }

	void	valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){};
	void	valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){};
	void	valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){};
	void	valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){};
	void	valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){};
    
    const int getID() { return _id; };
        
    ValueTree propertyTree;
    
private:
    int     _id;
    
};



#endif  // __BUTTONPROPERTYCONTAINER_H_B84412B7__
