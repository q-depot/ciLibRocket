
#ifndef CILIBROCKET_SLIDER
#define CILIBROCKET_SLIDER


#include "Rocket/Core.h"


class ciLibRocketSlider : public Rocket::Core::Element {
    
public:
    // Returns the baseline of the element, in pixels offset from the bottom of the element's content area.
    // @return The element's baseline. A negative baseline will be further 'up' the element, a positive on further 'down'.
//    virtual float GetBaseline() { return 0.0f; }
    
    // Gets the intrinsic dimensions of this element, if it is of a type that has an inherent size.
    // @param[in] dimensions The dimensions to size, if appropriate.
    // @return True if the element has intrinsic dimensions, false otherwise.
//    virtual bool GetIntrinsicDimensions( Rocket::Core::Vector2f& dimensions) { return false; }
    
    // Called for every event sent to this element or one of its descendants.
    // @param[in] event The event to process.
//    virtual void ProcessEvent(Rocket::Core::Event& event) {}
    
    // Called during the update loop after children are updated.
    virtual void OnUpdate() {}
    // Called during render after backgrounds, borders, decorators, but before children, are rendered.
    virtual void OnRender() {}
    
    // Called when attributes on the element are changed.
    // @param[in] changed_attributes The attributes changed on the element.
//    virtual void OnAttributeChange(const Rocket::Core::AttributeNameList& changed_attributes) {}
    // Called when properties on the element are changed.
    // @param[in] changed_properties The properties changed on the element.
//    virtual void OnPropertyChange(const Rocket::Core::PropertyNameList& changed_properties) {}
    
    // Called when a child node has been added somewhere in the hierarchy.
    // @param[in] child The element that has been added. This may be this element.
    virtual void OnChildAdd(Rocket::Core::Element* child) {}
    // Called when a child node has been removed somewhere in the hierarchy.
    // @param[in] child The element that has been removed. This may be this element.
    virtual void OnChildRemove(Rocket::Core::Element* child) {}
    
    // Gets the markup and content of the element.
    // @param[out] content The content of the element.
    virtual void GetInnerRML( Rocket::Core::String& content) {}
    // Returns the RML of this element and all children.
    // @param[out] content The content of this element and those under it, in XML form.
    virtual void GetRML( Rocket::Core::String& content) {}

};


#endif
