
#ifndef CILIBROCKET_ELEMENT_INSTANCER
#define CILIBROCKET_ELEMENT_INSTANCER

#include "Rocket/Core.h"


class ciLibRocketElementInstancer : public  Rocket::Core::ElementInstancer {
    
public:
    
    ciLibRocketElementInstancer() {}
    
    ~ciLibRocketElementInstancer() {}
    
    // Instances an element given the tag name and attributes.
    // @param[in] parent The element the new element is destined to be parented to.
    // @param[in] tag The tag of the element to instance.
    // @param[in] attributes Dictionary of attributes.
    virtual Rocket::Core::Element* InstanceElement(Rocket::Core::Element* parent, const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes) = 0;
    
    // Releases an element instanced by this instancer.
    // @param[in] element The element to release.
    virtual void ReleaseElement(Rocket::Core::Element* element) = 0;
    
    // Release the instancer.
    virtual void Release() = 0;

private:

};


#endif
