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

#ifndef __JUCE_MODALCOMPONENTMANAGER_JUCEHEADER__
#define __JUCE_MODALCOMPONENTMANAGER_JUCEHEADER__

#include "../../core/juce_Singleton.h"
#include "../../events/juce_AsyncUpdater.h"
#include "../../utilities/juce_DeletedAtShutdown.h"


//==============================================================================
/**
    Manages the system's stack of modal components.

    Normally you'll just use the Component methods to invoke modal states in components,
    and won't have to deal with this class directly, but this is the singleton object that's
    used internally to manage the stack.

    @see Component::enterModalState, Component::exitModalState, Component::isCurrentlyModal,
         Component::getCurrentlyModalComponent, Component::isCurrentlyBlockedByAnotherModalComponent
*/
class JUCE_API  ModalComponentManager   : public AsyncUpdater,
                                          public DeletedAtShutdown
{
public:
    //==============================================================================
    /** Receives callbacks when a modal component is dismissed.

        You can register a callback using Component::enterModalState() or
        ModalComponentManager::attachCallback().

        For some quick ways of creating callback objects, see the ModalCallbackFunction class.
        @see ModalCallbackFunction
    */
    class Callback
    {
    public:
        /** */
        Callback() {}

        /** Destructor. */
        virtual ~Callback() {}

        /** Called to indicate that a modal component has been dismissed.

            You can register a callback using Component::enterModalState() or
            ModalComponentManager::attachCallback().

            The returnValue parameter is the value that was passed to Component::exitModalState()
            when the component was dismissed.

            The callback object will be deleted shortly after this method is called.
        */
        virtual void modalStateFinished (int returnValue) = 0;
    };

    //==============================================================================
    /** Returns the number of components currently being shown modally.
        @see getModalComponent
    */
    int getNumModalComponents() const;

    /** Returns one of the components being shown modally.
        An index of 0 is the most recently-shown, topmost component.
    */
    Component* getModalComponent (int index) const;

    /** Returns true if the specified component is in a modal state. */
    bool isModal (Component* component) const;

    /** Returns true if the specified component is currently the topmost modal component. */
    bool isFrontModalComponent (Component* component) const;

    /** Adds a new callback that will be called when the specified modal component is dismissed.

        If the component is modal, then when it is dismissed, either by being hidden, or by calling
        Component::exitModalState(), then the Callback::modalStateFinished() method will be
        called.

        Each component can have any number of callbacks associated with it, and this one is added
        to that list.

        The object that is passed in will be deleted by the manager when it's no longer needed. If
        the given component is not currently modal, the callback object is deleted immediately and
        no action is taken.
    */
    void attachCallback (Component* component, Callback* callback);

    /** Brings any modal components to the front. */
    void bringModalComponentsToFront (bool topOneShouldGrabFocus = true);

   #if JUCE_MODAL_LOOPS_PERMITTED
    /** Runs the event loop until the currently topmost modal component is dismissed, and
        returns the exit code for that component.
    */
    int runEventLoopForCurrentComponent();
   #endif

    //==============================================================================
    juce_DeclareSingleton_SingleThreaded_Minimal (ModalComponentManager);

protected:
    /** Creates a ModalComponentManager.
        You shouldn't ever call the constructor - it's a singleton, so use ModalComponentManager::getInstance()
    */
    ModalComponentManager();

    /** Destructor. */
    ~ModalComponentManager();

    /** @internal */
    void handleAsyncUpdate();

private:
    //==============================================================================
    class ModalItem;
    class ReturnValueRetriever;

    friend class Component;
    friend class OwnedArray <ModalItem>;
    OwnedArray <ModalItem> stack;

    void startModal (Component* component);
    void endModal (Component* component, int returnValue);
    void endModal (Component* component);

    JUCE_DECLARE_NON_COPYABLE (ModalComponentManager);
};

//==============================================================================
/**
    This class provides some handy utility methods for creating ModalComponentManager::Callback
    objects that will invoke a static function with some parameters when a modal component is dismissed.
*/
class ModalCallbackFunction
{
public:
    //==============================================================================
    /** This is a utility function to create a ModalComponentManager::Callback that will
        call a static function with a parameter.

        The function that you supply must take two parameters - the first being an int, which is
        the result code that was used when the modal component was dismissed, and the second
        can be a custom type. Note that this custom value will be copied and stored, so it must
        be a primitive type or a class that provides copy-by-value semantics.

        E.g. @code
        static void myCallbackFunction (int modalResult, double customValue)
        {
            if (modalResult == 1)
                doSomethingWith (customValue);
        }

        Component* someKindOfComp;
        ...
        someKindOfComp->enterModalState (ModalCallbackFunction::create (myCallbackFunction, 3.0));
        @endcode
        @see ModalComponentManager::Callback
    */
    template <typename ParamType>
    static ModalComponentManager::Callback* create (void (*functionToCall) (int, ParamType),
                                                    ParamType parameterValue)
    {
        return new FunctionCaller1 <ParamType> (functionToCall, parameterValue);
    }

    //==============================================================================
    /** This is a utility function to create a ModalComponentManager::Callback that will
        call a static function with two custom parameters.

        The function that you supply must take three parameters - the first being an int, which is
        the result code that was used when the modal component was dismissed, and the next two are
        your custom types. Note that these custom values will be copied and stored, so they must
        be primitive types or classes that provide copy-by-value semantics.

        E.g. @code
        static void myCallbackFunction (int modalResult, double customValue1, String customValue2)
        {
            if (modalResult == 1)
                doSomethingWith (customValue1, customValue2);
        }

        Component* someKindOfComp;
        ...
        someKindOfComp->enterModalState (ModalCallbackFunction::create (myCallbackFunction, 3.0, String ("xyz")));
        @endcode
        @see ModalComponentManager::Callback
    */
    template <typename ParamType1, typename ParamType2>
    static ModalComponentManager::Callback* withParam (void (*functionToCall) (int, ParamType1, ParamType2),
                                                       ParamType1 parameterValue1,
                                                       ParamType2 parameterValue2)
    {
        return new FunctionCaller2 <ParamType1, ParamType2> (functionToCall, parameterValue1, parameterValue2);
    }

    //==============================================================================
    /** This is a utility function to create a ModalComponentManager::Callback that will
        call a static function with a component.

        The function that you supply must take two parameters - the first being an int, which is
        the result code that was used when the modal component was dismissed, and the second
        can be a Component class. The component will be stored as a WeakReference, so that if it gets
        deleted before this callback is invoked, the pointer that is passed to the function will be null.

        E.g. @code
        static void myCallbackFunction (int modalResult, Slider* mySlider)
        {
            if (modalResult == 1 && mySlider != nullptr) // (must check that mySlider isn't null in case it was deleted..)
                mySlider->setValue (0.0);
        }

        Component* someKindOfComp;
        Slider* mySlider;
        ...
        someKindOfComp->enterModalState (ModalCallbackFunction::forComponent (myCallbackFunction, mySlider));
        @endcode
        @see ModalComponentManager::Callback
    */
    template <class ComponentType>
    static ModalComponentManager::Callback* forComponent (void (*functionToCall) (int, ComponentType*),
                                                          ComponentType* component)
    {
        return new ComponentCaller1 <ComponentType> (functionToCall, component);
    }

    //==============================================================================
    /** Creates a ModalComponentManager::Callback that will call a static function with a component.

        The function that you supply must take three parameters - the first being an int, which is
        the result code that was used when the modal component was dismissed, the second being a Component
        class, and the third being a custom type (which must be a primitive type or have copy-by-value semantics).
        The component will be stored as a WeakReference, so that if it gets deleted before this callback is
        invoked, the pointer that is passed into the function will be null.

        E.g. @code
        static void myCallbackFunction (int modalResult, Slider* mySlider, String customParam)
        {
            if (modalResult == 1 && mySlider != nullptr) // (must check that mySlider isn't null in case it was deleted..)
                mySlider->setName (customParam);
        }

        Component* someKindOfComp;
        Slider* mySlider;
        ...
        someKindOfComp->enterModalState (ModalCallbackFunction::forComponent (myCallbackFunction, mySlider, String ("hello")));
        @endcode
        @see ModalComponentManager::Callback
    */
    template <class ComponentType, typename ParamType>
    static ModalComponentManager::Callback* forComponent (void (*functionToCall) (int, ComponentType*, ParamType),
                                                          ComponentType* component,
                                                          ParamType param)
    {
        return new ComponentCaller2 <ComponentType, ParamType> (functionToCall, component, param);
    }

private:
    //==============================================================================
    template <typename ParamType>
    class FunctionCaller1  : public ModalComponentManager::Callback
    {
    public:
        typedef void (*FunctionType) (int, ParamType);

        FunctionCaller1 (FunctionType& function_, ParamType& param_)
            : function (function_), param (param_) {}

        void modalStateFinished (int returnValue)  { function (returnValue, param); }

    private:
        const FunctionType function;
        ParamType param;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunctionCaller1);
    };

    template <typename ParamType1, typename ParamType2>
    class FunctionCaller2  : public ModalComponentManager::Callback
    {
    public:
        typedef void (*FunctionType) (int, ParamType1, ParamType2);

        FunctionCaller2 (FunctionType& function_, ParamType1& param1_, ParamType2& param2_)
            : function (function_), param1 (param1_), param2 (param2_) {}

        void modalStateFinished (int returnValue)   { function (returnValue, param1, param2); }

    private:
        const FunctionType function;
        ParamType1 param1;
        ParamType2 param2;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FunctionCaller2);
    };

    template <typename ComponentType>
    class ComponentCaller1  : public ModalComponentManager::Callback
    {
    public:
        typedef void (*FunctionType) (int, ComponentType*);

        ComponentCaller1 (FunctionType& function_, ComponentType* comp_)
            : function (function_), comp (comp_) {}

        void modalStateFinished (int returnValue)
        {
            function (returnValue, static_cast <ComponentType*> (comp.get()));
        }

    private:
        const FunctionType function;
        WeakReference<Component> comp;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentCaller1);
    };

    template <typename ComponentType, typename ParamType1>
    class ComponentCaller2  : public ModalComponentManager::Callback
    {
    public:
        typedef void (*FunctionType) (int, ComponentType*, ParamType1);

        ComponentCaller2 (FunctionType& function_, ComponentType* comp_, ParamType1 param1_)
            : function (function_), comp (comp_), param1 (param1_) {}

        void modalStateFinished (int returnValue)
        {
            function (returnValue, static_cast <ComponentType*> (comp.get()), param1);
        }

    private:
        const FunctionType function;
        WeakReference<Component> comp;
        ParamType1 param1;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentCaller2);
    };

    ModalCallbackFunction();
    ~ModalCallbackFunction();
    JUCE_DECLARE_NON_COPYABLE (ModalCallbackFunction);
};


#endif   // __JUCE_MODALCOMPONENTMANAGER_JUCEHEADER__
