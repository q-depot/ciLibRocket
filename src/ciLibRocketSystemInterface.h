
#ifndef CILIBROCKET_SYSTEMINTERFACE
#define CILIBROCKET_SYSTEMINTERFACE

#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Log.h>
#include <Rocket/Core/Types.h>

class ciLibRocketSystemInterface: public Rocket::Core::SystemInterface {

public:
    
	ciLibRocketSystemInterface() {}
	
    ~ciLibRocketSystemInterface() {}

    float GetElapsedTime() { return ci::app::getElapsedSeconds(); }

};

#endif
