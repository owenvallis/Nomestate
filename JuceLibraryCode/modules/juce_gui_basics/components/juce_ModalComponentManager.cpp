/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

BEGIN_JUCE_NAMESPACE

//==============================================================================
class ModalComponentManager::ModalItem  : public ComponentMovementWatcher
{
public:
    ModalItem (Component* const comp, const bool autoDelete_)
        : ComponentMovementWatcher (comp),
          component (comp), returnValue (0),
          isActive (true), autoDelete (autoDelete_)
    {
        jassert (comp != nullptr);
    }

    void componentMovedOrResized (bool, bool) {}

    void componentPeerChanged()
    {
        if (! component->isShowing())
            cancel();
    }

    void componentVisibilityChanged()
    {
        if (! component->isShowing())
            cancel();
    }

    void componentBeingDeleted (Component& comp)
    {
        ComponentMovementWatcher::componentBeingDeleted (comp);

        if (component == &comp || comp.isParentOf (component))
        {
            autoDelete = false;
            cancel();
        }
    }

    void cancel()
    {
        if (isActive)
        {
            isActive = false;
            ModalComponentManager::getInstance()->triggerAsyncUpdate();
        }
    }

    Component* component;
    OwnedArray<Callback> callbacks;
    int returnValue;
    bool isActive, autoDelete;

private:
    JUCE_DECLARE_NON_COPYABLE (ModalItem);
};

//==============================================================================
ModalComponentManager::ModalComponentManager()
{
}

ModalComponentManager::~ModalComponentManager()
{
    clearSingletonInstance();
}

juce_ImplementSingleton_SingleThreaded (ModalComponentManager);


//==============================================================================
void ModalComponentManager::startModal (Component* component, bool autoDelete)
{
    if (component != nullptr)
        stack.add (new ModalItem (component, autoDelete));
}

void ModalComponentManager::attachCallback (Component* component, Callback* callback)
{
    if (callback != nullptr)
    {
        ScopedPointer<Callback> callbackDeleter (callback);

        for (int i = stack.size(); --i >= 0;)
        {
            ModalItem* const item = stack.getUnchecked(i);

            if (item->component == component)
            {
                item->callbacks.add (callback);
                callbackDeleter.release();
                break;
            }
        }
    }
}

void ModalComponentManager::endModal (Component* component)
{
    for (int i = stack.size(); --i >= 0;)
    {
        ModalItem* const item = stack.getUnchecked(i);

        if (item->component == component)
            item->cancel();
    }
}

void ModalComponentManager::endModal (Component* component, int returnValue)
{
    for (int i = stack.size(); --i >= 0;)
    {
        ModalItem* const item = stack.getUnchecked(i);

        if (item->component == component)
        {
            item->returnValue = returnValue;
            item->cancel();
        }
    }
}

int ModalComponentManager::getNumModalComponents() const
{
    int n = 0;
    for (int i = 0; i < stack.size(); ++i)
        if (stack.getUnchecked(i)->isActive)
            ++n;

    return n;
}

Component* ModalComponentManager::getModalComponent (const int index) const
{
    int n = 0;
    for (int i = stack.size(); --i >= 0;)
    {
        const ModalItem* const item = stack.getUnchecked(i);
        if (item->isActive)
            if (n++ == index)
                return item->component;
    }

    return nullptr;
}

bool ModalComponentManager::isModal (Component* const comp) const
{
    for (int i = stack.size(); --i >= 0;)
    {
        const ModalItem* const item = stack.getUnchecked(i);
        if (item->isActive && item->component == comp)
            return true;
    }

    return false;
}

bool ModalComponentManager::isFrontModalComponent (Component* const comp) const
{
    return comp == getModalComponent (0);
}

void ModalComponentManager::handleAsyncUpdate()
{
    for (int i = stack.size(); --i >= 0;)
    {
        const ModalItem* const item = stack.getUnchecked(i);

        if (! item->isActive)
        {
            ScopedPointer<ModalItem> deleter (stack.removeAndReturn (i));
            Component::SafePointer<Component> compToDelete (item->autoDelete ? item->component : nullptr);

            for (int j = item->callbacks.size(); --j >= 0;)
                item->callbacks.getUnchecked(j)->modalStateFinished (item->returnValue);

            compToDelete.deleteAndZero();
        }
    }
}

void ModalComponentManager::bringModalComponentsToFront (bool topOneShouldGrabFocus)
{
    ComponentPeer* lastOne = nullptr;

    for (int i = 0; i < getNumModalComponents(); ++i)
    {
        Component* const c = getModalComponent (i);

        if (c == nullptr)
            break;

        ComponentPeer* peer = c->getPeer();

        if (peer != nullptr && peer != lastOne)
        {
            if (lastOne == nullptr)
            {
                peer->toFront (topOneShouldGrabFocus);

                if (topOneShouldGrabFocus)
                    peer->grabFocus();
            }
            else
                peer->toBehind (lastOne);

            lastOne = peer;
        }
    }
}

#if JUCE_MODAL_LOOPS_PERMITTED
class ModalComponentManager::ReturnValueRetriever     : public ModalComponentManager::Callback
{
public:
    ReturnValueRetriever (int& value_, bool& finished_) : value (value_), finished (finished_) {}

    void modalStateFinished (int returnValue)
    {
        finished = true;
        value = returnValue;
    }

private:
    int& value;
    bool& finished;

    JUCE_DECLARE_NON_COPYABLE (ReturnValueRetriever);
};

int ModalComponentManager::runEventLoopForCurrentComponent()
{
    // This can only be run from the message thread!
    jassert (MessageManager::getInstance()->isThisTheMessageThread());

    Component* currentlyModal = getModalComponent (0);

    if (currentlyModal == nullptr)
        return 0;

    WeakReference<Component> prevFocused (Component::getCurrentlyFocusedComponent());

    int returnValue = 0;
    bool finished = false;
    attachCallback (currentlyModal, new ReturnValueRetriever (returnValue, finished));

    JUCE_TRY
    {
        while (! finished)
        {
            if  (! MessageManager::getInstance()->runDispatchLoopUntil (20))
                break;
        }
    }
    JUCE_CATCH_EXCEPTION

    if (prevFocused != nullptr)
        prevFocused->grabKeyboardFocus();

    return returnValue;
}
#endif

END_JUCE_NAMESPACE
