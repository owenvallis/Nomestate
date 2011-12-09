/*
  ==============================================================================

    PropertyGroup.cpp
    Created: 2 Dec 2010 8:59:52pm
    Author:  Haydxn

  ==============================================================================
*/

#include "PropertyGroup.h"

/**	Simple ValueSource class for wrapping manipulating multiple Value objects,
	so they can all be changed from a single object. */

class MultiValueProxySource	:	public Value::ValueSource
{
public:

	MultiValueProxySource ()
	{
	}

	~MultiValueProxySource ()
	{
	}

	void addTarget (const Value& target)
	{
		targets.add (target);
	}

	bool targetsEqual () const
	{
		if (targets.size() > 1)
		{
			for (int i=1; i<targets.size(); i++)
			{
				if (targets.getUnchecked(i).getValue() != targets.getUnchecked(i-1).getValue())
					return false;
			}
		}
		return true;
	}

	virtual var getValue () const
	{
		if (targets.size())
		{
			if (targetsEqual())
				return targets.getFirst().getValue();
		}
		return var::null;
	}

	void setValue (const var& newValue)
	{
		if (getValue() == newValue)
			return;

		int n = targets.size();
		for (int i=0; i<n; i++)
		{
			targets[i].setValue (newValue);
		}
	}

private:

	Array<Value>	targets;
};

//----------------------------------------------------------------------------------------

const Identifier PropertyDescriptor::nodeType		= "PropertyDescriptor";
const Identifier PropertyDescriptor::id				= "Id";
const Identifier PropertyDescriptor::label			= "Label";
const Identifier PropertyDescriptor::control		= "Control";


PropertyDescriptor::PropertyDescriptor (const Identifier& propId, const String& uiLabel, const Identifier& controlType)
:	node (nodeType)
{
	node.setProperty(id, propId.toString(), NULL);
	node.setProperty(label, uiLabel, NULL);
	node.setProperty(control, controlType.toString(), NULL);
}

PropertyDescriptor::PropertyDescriptor (const PropertyDescriptor& other)
:	node (other.getNode())
{
}

PropertyDescriptor::PropertyDescriptor (const ValueTree& treeData)
:	node (treeData)
{
	if (!node.hasType(nodeType))
	{
		// not valid data!
		node = ValueTree();
	}
}

PropertyDescriptor& PropertyDescriptor::operator= (const PropertyDescriptor& other)
{
	node = other.getNode();
	return *this;
}



Identifier PropertyDescriptor::getId () const
{
	return Identifier(node.getProperty (id)); //added cast
}

Identifier PropertyDescriptor::getGroupId () const
{
	ValueTree group = node.getParent();

	if (group.hasType(PropertyGroup::nodeType))
	{
		return Identifier(group.getProperty (PropertyGroup::id)); //added cast
	}
	else return Identifier();
}

String PropertyDescriptor::getLabel () const
{
	return node.getProperty(label);
}

Identifier PropertyDescriptor::getControlType () const
{
	return Identifier(node.getProperty(control)); //added cast
}

ValueTree PropertyDescriptor::getNode () const
{
	return node;
}


//----------------------------------------------------------------------------------------

const Identifier PropertyGroup::nodeType		= "Group";
const Identifier PropertyGroup::id				= "Id";
const Identifier PropertyGroup::label			= "Label";

PropertyGroup::PropertyGroup (const Identifier& propertyGroupId, const String& title)
{
	node = ValueTree (nodeType);
	node.setProperty (id, propertyGroupId.toString(), NULL);
	setLabel (title);
}

PropertyGroup::~PropertyGroup ()
{
}

void PropertyGroup::setLabel (const String& title_)
{
	node.setProperty (label, title_, NULL);
}

Identifier PropertyGroup::getId () const
{
	return Identifier(node.getProperty (id)); //added cast
}

String PropertyGroup::getLabel () const
{
	return node.getProperty (label);
}

int PropertyGroup::getNumProperties () const
{
	return node.getNumChildren ();
}

PropertyDescriptor PropertyGroup::getProperty (int index) const
{
	return node.getChild (index);
}

PropertyDescriptor PropertyGroup::getProperty (const Identifier& propId) const
{
	return PropertyDescriptor (node.getChildWithProperty (PropertyDescriptor::id, propId.toString()));
}

void PropertyGroup::addProperty (const Identifier& id, const String& label, const Identifier& control)
{
	PropertyDescriptor prop (id, label, control);
	addProperty (prop);
}

void PropertyGroup::addProperty (const PropertyDescriptor& prop)
{
	jassert (!prop.getNode().getParent().isValid());
	// .. well, i think ValueTree will do this check anyway, but surely can't hurt.

	ValueTree existing (node.getChildWithProperty (PropertyDescriptor::id, prop.getId().toString()));
	if (existing.isValid())
	{
		jassertfalse; // A property with this name already exists in this group.
		node.removeChild (existing,NULL);
	}
	node.addChild (prop.getNode(),-1,NULL);
}




Value PropertyGroup::getTargetPropertyValue (const PropertyDescriptor& prop, const Array<PropertyGroup::Container*>& containers) const
{
	if (containers.size() == 0)
		return Value(); // nothing here! :O

	if (containers.size() == 1)
	{
		// Only one target, get the value directly...
		return containers.getFirst()->getGroupProperty (getId(), prop);
	}
	else
	{
		// We must make a proxy Value to wrap all the values...
		MultiValueProxySource* proxy = new MultiValueProxySource;

		int n = containers.size();
		for (int i=0; i<n; i++)
		{
			PropertyGroup::Container* c = containers[i];
			proxy->addTarget ( c->getGroupProperty (getId(), prop) );
		}
		return Value (proxy);
	}
}



void PropertyGroup::getCommonPropertyGroups (const Array<PropertyGroup::Container*>& containers, PropertyGroup::IdList& common)
{
	// NOTE: not concerned with being optimal here yet...
	// [the group list is re-acquired from the targets many times here...
	//  that's pretty terrible, but will do for prototyping purposes].

	PropertyGroup::Container* target;
	int n = containers.size();

	// First, assemble a combined list of all relevant propertyGroups...
	for (int i=0; i<n; i++)
	{
		// Get propertyGroups from this target...
		PropertyGroup::IdList propertyGroups;
		target = containers.getUnchecked(i);
		target->getPropertyGroups (propertyGroups);

		// Add them to the common list...
		for (int j=0; j<propertyGroups.size(); j++)
			common.addIfNotAlreadyThere (propertyGroups.getUnchecked(j));
	}

	// Now, remove any that aren't present in ALL containers...
	int index = 0;
	while (index < common.size())
	{
		Identifier propertyGroupId (common.getUnchecked(index));

		bool absent = false;
		for (int i=0; i<n; i++)
		{
			PropertyGroup::IdList propertyGroups;
			target = containers.getUnchecked(i);
			target->getPropertyGroups (propertyGroups);

			if (!propertyGroups.contains(propertyGroupId))
			{
				absent = true;
				break;
			}
		}

		if (absent)
			common.remove (index);
		else index++;
	}
}


//-------------------------------------------------------------------------


PropertyGroup::ComponentFactory::ComponentFactory ()
{
	buttonModes.add("Toggle");
	buttonModes.add("Trigger");
	buttonModes.add("Note");
	buttonModeValues.add(var(0));
	buttonModeValues.add(var(1));
	buttonModeValues.add(var(2));
}

PropertyGroup::ComponentFactory::~ComponentFactory ()
{
}

PropertyComponent* PropertyGroup::ComponentFactory::createEditor (const PropertyGroup& group, const PropertyDescriptor& prop, const Value& value)
{
	//--------------------------
	// Default implementation:
	//--------------------------
	// Just return a default editor
	return createDefaultEditor (group, prop, value);
}

void PropertyGroup::ComponentFactory::createEditorComponents (const PropertyGroup& group, Array<PropertyComponent*>& editors, const Array<PropertyGroup::Container*>& containers)
{
	//--------------------------
	// Default implementation:
	//--------------------------
	// Step through all the properties in this group, and create an editor for each one.
	int n = group.getNumProperties();
	for (int i=0; i<n; i++)
	{
		// Get the property...
		PropertyDescriptor prop (group.getProperty(i));
		// Get a wrapped Value object for the target containers...
		Value value(group.getTargetPropertyValue (prop, containers));
		// Create an editor...
		PropertyComponent* editor = createEditor (group, prop, value);
		if (editor)
			editors.add (editor);
	}
}


/** This creates a default editor component [a plain text editor]. */
PropertyComponent* PropertyGroup::ComponentFactory::createDefaultEditor (const PropertyGroup& group, const PropertyDescriptor& prop, const Value& value)
{
	if (prop.getLabel() == "ButtonMode"){
		return new ChoicePropertyComponent (value, prop.getLabel(), buttonModes, buttonModeValues);
	}
	else if (prop.getLabel() == "Pressure"){
		return new BooleanPropertyComponent (value, prop.getLabel(), "Pressure");
		std::cout << "Pressure..." << std::endl;
	}
	else if (prop.getLabel() == "Colour"){
		return new ColourSelectorPropertyComponent(value, prop.getLabel());
	}
	//If we get an unknown param, use a TextBox...
	return new TextPropertyComponent (value, prop.getLabel(), 127, false);
}


//-------------------------------------------------------------------------


PropertyGroupLibrary::PropertyGroupLibrary ()
{
}

PropertyGroupLibrary::~PropertyGroupLibrary ()
{
}

void PropertyGroupLibrary::registerPropertyGroup (PropertyGroup* newAspect)
{
	PropertyGroup* existing = getPropertyGroup (newAspect->getId());
	if (existing)
	{
		if (existing == newAspect)
			return; // already there...

		// don't want a clash... remove or assert? let's try both...
		propertyGroups.removeObject (existing);
		jassertfalse;
	}
	
	propertyGroups.add (newAspect);
}

int PropertyGroupLibrary::getNumPropertyGroups () const
{
	return propertyGroups.size();
}

PropertyGroup* PropertyGroupLibrary::getPropertyGroup (int index) const
{
	return propertyGroups[index];
}

PropertyGroup* PropertyGroupLibrary::getPropertyGroup (const Identifier& propertyGroupId) const
{
	int n = propertyGroups.size();
	for (int i=0; i<n; i++)
	{
		PropertyGroup* group = propertyGroups.getUnchecked(i);
		if (group->getId() == propertyGroupId)
			return group;
	}
	return NULL;
}



//---------------------------------------------------------------------------------------


PropertyGroupEditor::PropertyGroupEditor (PropertyGroup::Source* sourceToUse, PropertyGroup::ComponentFactory* factoryToUse)
:	aspectSource(sourceToUse),
	factory(factoryToUse)
{
	propPanel = new PropertyPanel;
	propPanel->setMessageWhenEmpty("Please Select Buttons...");
	addAndMakeVisible (propPanel);
}

PropertyGroupEditor::~PropertyGroupEditor ()
{
}

void PropertyGroupEditor::resized ()
{
	propPanel->setBounds (0,0,getWidth(),getHeight());
}

void PropertyGroupEditor::paint(Graphics& g){
	g.setColour(Colour(100,100,100));
	g.fillRect(0, 0, getWidth(), getHeight());
}

PropertyPanel* PropertyGroupEditor::getPropertyPanel () const
{
	return propPanel;
}

PropertyGroup* PropertyGroupEditor::getPropertyGroup (const Identifier& propertyGroupId) const
{
	if (aspectSource)
		return aspectSource->getPropertyGroup (propertyGroupId);
	return NULL;
}

void PropertyGroupEditor::showPropertiesFor (const Array<PropertyGroup::Container*>& containers)
{
	propPanel->clear ();

	// First, get the common property families...
	PropertyGroup::IdList commonAspects;
	PropertyGroup::getCommonPropertyGroups (containers, commonAspects);

	int n = commonAspects.size();
	for (int i=0; i<n; i++)
	{
		// For each group, we want to add the properties from the containers...
		PropertyGroup* group = getPropertyGroup (commonAspects.getUnchecked(i));
		if (group)
		{
			Array<PropertyComponent*> editorComps;

			factory->createEditorComponents (*group, editorComps, containers);
			if (editorComps.size())
			{
				propPanel->addSection (group->getLabel(), editorComps, true);
			}
		}
	}
}

void PropertyGroupEditor::showPropertiesFor (PropertyGroup::Container* container)
{
	// we COULD do this directly, but right now I can't be bothered.
	Array<PropertyGroup::Container*> containers;
	containers.add (container);
	showPropertiesFor (containers);
}


