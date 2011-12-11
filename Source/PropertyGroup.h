/*
  ==============================================================================

    PropertyGroup.h
    Created: 2 Dec 2010 8:59:52pm
    Author:  Haydxn

  ==============================================================================
*/

#ifndef __PROPERTYGROUP_H_
#define __PROPERTYGROUP_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include "ColourSelectorPropertyComponent.h"

/**
	Describes a single editable property of a particular group.
*/
class PropertyDescriptor
{
public:

	static const Identifier nodeType;
	static const Identifier id;
	static const Identifier label;
	static const Identifier control;

	PropertyDescriptor (const Identifier& id, const String& label, const Identifier& controlType = String::empty);
	PropertyDescriptor (const PropertyDescriptor& other);
	PropertyDescriptor (const ValueTree& treeData);
	PropertyDescriptor& operator= (const PropertyDescriptor& other);
	
	/** Returns this property's identifier. */
	Identifier getId () const;
	/** Returns the identifier of the group this property belongs to. */
	Identifier getGroupId () const;
	/** Returns the user-friendly name of this property. */
	String getLabel () const;
	/** Returns the suggested control-type id. */
	Identifier getControlType () const;

	/** Returns the ValueTree node holding this property's information. This can
		be used to get/set any custom settings; e.g. valid range information for
		the control. */
	ValueTree getNode () const;

private:

	ValueTree	node;
};


/**
	This class describes a collection of properties relating to a specific
	group of an object, which may be common across various types (e.g.
	subclasses). It is also responsible for instantiating PropertyComponents
	suitable for manipulating such properties on an PropertyGroupEditor.
*/
class PropertyGroup
{
public:

	typedef Array<Identifier> IdList;

	static const Identifier nodeType;
	static const Identifier	id;
	static const Identifier label;

	/** Create a new PropertyGroup with the minimum required information. */
	PropertyGroup (const Identifier& id, const String& label);
	virtual ~PropertyGroup ();




	/** This is a base for objects which need to expose properties for editing
		via the PropertyGroupEditor.
		
		It has two main responsibilities. Firstly, it must be able to provide a
		list of supported PropertyGroups (as a simple array of identifiers).
		Secondly, it must return a Value object representing a given editable
		group property. */
	class Container
	{
	public:
		
		/** This simply needs to populate the provided array with the ids of all 
			editable propertyGroups this object type wishes to expose. */
		virtual void getPropertyGroups (PropertyGroup::IdList& groupIds) = 0;

		/** This should return a Value object representing the specified property. 
			How you do this depends upon the nature of the object and the manner in
			which its propertyGroups are stored.

			This is simplest if your object's data is held in a ValueTree, as they
			can already return Values. If you've also defined the various group property
			IDs to match actual properties in your ValueTree, this is very straightforward;
			a call to myNode.getPropertyAsValue(propInfo.getId()) would be all you need.
			
			If your data is more complex (or there are overlapping ids across propertyGroups),
			you'll need to examine the provided PropertyDescriptor information
			(using getGroupId() and getId()) to determine what you need to return.

			If you're not using a ValueTree, you'll probably need to make your own 
			ValueSource types to interact with your data (and wrap them in a Value). */
		virtual Value getGroupProperty (const Identifier& groupId, const PropertyDescriptor& propInfo) = 0;

	private:
	};




	/** This simple abstract class is used by an PropertyGroupEditor to acquire PropertyGroups. */
	class Source
	{
	public:
		
		/** This must be defined to locate and return the appropriate PropertyGroup
			for the given identifier. */
		virtual PropertyGroup* getPropertyGroup (const Identifier& propertyGroupId) const = 0;
	};



	class ComponentFactory
	{
	public:

		ComponentFactory ();
		virtual ~ComponentFactory ();

		/** This should return a new PropertyComponent for the specified property
			(using the given Value object as a target). The default implementation simply
			calls createDefaultEditor(). */
		virtual PropertyComponent* createEditor (const PropertyGroup& group, const PropertyDescriptor& prop, const Value& value);

		/** This fills the 'editors' array with all the PropertyComponents required to
			provide an interface to the specified group. These components will be added 
			to the calling PropertyGroupEditor (under a suitable heading) automatically.

			You can safely ignore this function for most cases!

			The default implementation creates individual components for each property in 
			the group (using getTargetPropertyValue() and createEditor()). For most cases,
			this is all you'd need. However, it's possible to override it if you need more 
			specialised property editors (e.g. a special single-panel editor for multiple 
			values). */
		virtual void createEditorComponents (const PropertyGroup& group, Array<PropertyComponent*>& editors, const Array<Container*>& containers);


		/** This creates a default editor component [a plain text editor]. */
		PropertyComponent* createDefaultEditor (const PropertyGroup& group, const PropertyDescriptor& prop, const Value& value);

	private:
		StringArray							buttonModes;
		Array<var>							buttonModeValues;
	};



	/** Set the user-friendly title for this group. This is the text that will be
		used as a section heading in an PropertyGroupEditor. */
	void setLabel (const String& title);

	/** Returns this group's unique identifier. */
	Identifier getId () const;
	/** Returns this group's title. */
	String getLabel () const;

	/** Returns the number of properties belonging to this group. */
	int getNumProperties () const;
	/** Returns a property of this group by index. */
	PropertyDescriptor getProperty (int index) const;
	/** Returns a property of this group by its identifier. */
	PropertyDescriptor getProperty (const Identifier& id) const;
	/** Create and add a basic property to this group. */
	void addProperty (const Identifier& id, const String& title, const Identifier& control);
	/** Add a pre-constructed property to this group. */
	void addProperty (const PropertyDescriptor& prop);

	/** This will return a single Value object wrapping the corresponding property in
		the targets. It uses a special multi-target proxy if there are multiple containers,
		otherwise it will use the single container's Value directly. */
	Value getTargetPropertyValue (const PropertyDescriptor& prop, const Array<Container*>& containers) const;

	/** This finds out which PropertyGroups are common across all of the provided containers. */
	static void getCommonPropertyGroups (const Array<Container*>& containers, IdList& common);

private:

	ValueTree node;

};


/** This is a simple helper class for registering (and take ownership of)
	PropertyGroups. It's also a PropertyGroup::Source, so you can just point
	a PropertGroupEditor at one of these. */
class PropertyGroupLibrary	:	public PropertyGroup::Source
{
public:

	PropertyGroupLibrary ();
	virtual ~PropertyGroupLibrary ();

	void registerPropertyGroup (PropertyGroup* newAspect);
    void unregisterPropertyGroup (PropertyGroup* newAspect);
	int getNumPropertyGroups () const;
	PropertyGroup* getPropertyGroup (int index) const;
	PropertyGroup* getPropertyGroup (const Identifier& propertyGroupId) const;

private:

	OwnedArray<PropertyGroup>	propertyGroups;

};


/** Wraps a PropertyPanel with functionality to work with PropertyGroups. 
	This allows the panel to display PropertyComponents which can edit
	common properties of multiple objects at once. */
class PropertyGroupEditor	:	public Component
{
public:

	/** Create an PropertyGroupEditor. Requires a source (which provides the editor
		with the PropertyGroup instances necessary to populate the panel for
		a given set of editable containers) and a factory (for generating components). */
	PropertyGroupEditor (PropertyGroup::Source* sourceToUse, PropertyGroup::ComponentFactory* factoryToUse);
	virtual ~PropertyGroupEditor ();

	void resized ();
	void paint(Graphics& g);
	void showPropertiesFor (const Array<PropertyGroup::Container*>& containers);
	void showPropertiesFor (PropertyGroup::Container* container);

	PropertyPanel* getPropertyPanel () const;

	PropertyGroup* getPropertyGroup (const Identifier& propertyGroupId) const;

private:

	ScopedPointer<PropertyPanel>		propPanel;
	PropertyGroup::Source*				aspectSource;
	PropertyGroup::ComponentFactory*	factory;

};




#endif//__PROPERTYGROUP_H_
