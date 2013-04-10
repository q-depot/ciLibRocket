
#ifndef CILIBROCKET_SLIDER
#define CILIBROCKET_SLIDER


#include "Rocket/Core.h"


class ciLibRocketSlider : public Rocket::Core::Element {
    
public:
    
    ciLibRocketSlider(const Rocket::Core::String& tag) : Rocket::Core::Element(tag)
    {
        ci::app::console() << "init slider!!!" << std::endl;
        
        SetAttribute( "foo", 10 );
        
        Rocket::Core::XMLAttributes rocketAttributes;
        mSliderHandler      =  Rocket::Core::Factory::InstanceElement( this, "*", "slider_handler", rocketAttributes );
        mSliderFg           =  Rocket::Core::Factory::InstanceElement( this, "*", "slider_fg", rocketAttributes );
//        mSliderButtonIncr   =  Rocket::Core::Factory::InstanceElement( this, "*", "slider_button_incr", rocketAttributes );
//        mSliderButtonDecr   =  Rocket::Core::Factory::InstanceElement( this, "*", "slider_button_decr", rocketAttributes );        
        
//        Rocket::Core::Element* mSliderTextfield;
//        Rocket::Core::Element* mName;
        
        
        AppendChild( mSliderFg );
        AppendChild( mSliderHandler );
        
        //
//        if ( mHandler == NULL )
//            ci::app::console() << "WTF?" << std::endl;
//        return new ofxLibRocketElement(el);
    }
    
    ~ciLibRocketSlider() {}
    
    // Returns the baseline of the element, in pixels offset from the bottom of the element's content area.
    // @return The element's baseline. A negative baseline will be further 'up' the element, a positive on further 'down'.
//    virtual float GetBaseline() { return 0.0f; }
    
    // Gets the intrinsic dimensions of this element, if it is of a type that has an inherent size.
    // @param[in] dimensions The dimensions to size, if appropriate.
    // @return True if the element has intrinsic dimensions, false otherwise.
//    virtual bool GetIntrinsicDimensions( Rocket::Core::Vector2f& dimensions) { return false; }
    
    // Called for every event sent to this element or one of its descendants.
    // @param[in] event The event to process.
    void ProcessEvent(Rocket::Core::Event& event)
    {
        Rocket::Core::Element::ProcessEvent( event );
        ci::app::console() << ci::app::getElapsedSeconds() << " event" << std::endl;
        
//        mHandler->SetAttribute( "left", 50 );
//        if (event == "dragdrop")
//        {
//            Rocket::Core::Element* dest_container = event.GetCurrentElement();
//            Rocket::Core::Element* dest_element = event.GetTargetElement();
//            Rocket::Core::Element* drag_element = *static_cast< Rocket::Core::Element** >(event.GetParameter< void* >("drag_element", NULL));
//            
//            if (dest_container == dest_element)
//            {
//                // The dragged element was dragged directly onto a container.
//                drag_element->GetParentNode()->RemoveChild(drag_element);
//                dest_container->AppendChild(drag_element);
//            }
//            else
//            {
//                // The dragged element was dragged onto an item inside a container. In order to get the
//                // element in the right place, it will be inserted into the container before the item
//                // it was dragged on top of.
//                Rocket::Core::Element* insert_before = dest_element;
//                
//                // Unless of course if it was dragged on top of an item in its own container; we need
//                // to check then if it was moved up or down with the container.
//                if (drag_element->GetParentNode() == dest_container)
//                {
//                    // Check whether we're moving this icon from the left or the right.
//                    
//                    Rocket::Core::Element* previous_icon = insert_before->GetPreviousSibling();
//                    while (previous_icon != NULL)
//                    {
//                        if (previous_icon == drag_element)
//                        {
//                            insert_before = insert_before->GetNextSibling();
//                            break;
//                        }
//                        
//                        previous_icon = previous_icon->GetPreviousSibling();
//                    }
//                }
//                
//                drag_element->GetParentNode()->RemoveChild(drag_element);
//                dest_container->InsertBefore(drag_element, insert_before);
//            }
//        }
        
    }

    // Called during the update loop after children are updated.
    virtual void OnUpdate() {}
    // Called during render after backgrounds, borders, decorators, but before children, are rendered.
    virtual void OnRender() {}
    
    // Called when attributes on the element are changed.
    // @param[in] changed_attributes The attributes changed on the element.
    virtual void OnAttributeChange(const Rocket::Core::AttributeNameList& changed_attributes) {}
    // Called when properties on the element are changed.
    // @param[in] changed_properties The properties changed on the element.
    virtual void OnPropertyChange(const Rocket::Core::PropertyNameList& changed_properties) {}
    
    // Called when a child node has been added somewhere in the hierarchy.
    // @param[in] child The element that has been added. This may be this element.
    virtual void OnChildAdd(Rocket::Core::Element* child) {}
    // Called when a child node has been removed somewhere in the hierarchy.
    // @param[in] child The element that has been removed. This may be this element.
    virtual void OnChildRemove(Rocket::Core::Element* child) {}
    
    // Gets the markup and content of the element.
    // @param[out] content The content of the element.
//    virtual void GetInnerRML( Rocket::Core::String& content) {}
    // Returns the RML of this element and all children.
    // @param[out] content The content of this element and those under it, in XML form.
//    virtual void GetRML( Rocket::Core::String& content) {}

private:
    
    Rocket::Core::Element* mSliderFg;
    Rocket::Core::Element* mSliderHandler;
    Rocket::Core::Element* mSliderButtonIncr;
    Rocket::Core::Element* mSliderButtonDecr;
    Rocket::Core::Element* mSliderTextfield;
    Rocket::Core::Element* mName;
    
};


#endif
