
#ifndef CILIBROCKET
#define CILIBROCKET


#include "ciLibRocketRenderInterface.h"
#include "ciLibRocketSystemInterface.h"
//#include "ciLibRocketDocument.h"
//#include "ciLibRocketControls.h"
#include "Rocket/Core.h"
#include "Rocket/Debugger.h"
#include <Rocket/Controls.h>
//#include "ciLibRocketslider2d.h"
//#include "ciLibRocketVideo.h"
#include "ciLibRocketSlider.h"

class ciLibRocket : public Rocket::Core::Plugin {
    
public:
    
	ciLibRocket() {}
    
	~ciLibRocket();

	void setup();
    
    void loadDocument( ci::fs::path filePath );

    void render() { mContext->Render(); }
    
    void update() { mContext->Update(); }
    
	void registerCallbacks();

	void unregisterCallbacks();
    
    void toggleDebugger()   { Rocket::Debugger::SetVisible( !Rocket::Debugger::IsVisible() ); }
    void hideDebugger()     { Rocket::Debugger::SetVisible(false); }
    void showDebugger()     { Rocket::Debugger::SetVisible(true); }


private:
    
    bool mouseDown( ci::app::MouseEvent event );
    bool mouseUp( ci::app::MouseEvent event );
    bool mouseMove( ci::app::MouseEvent event );
    bool mouseDrag( ci::app::MouseEvent event );
    bool mouseWheel( ci::app::MouseEvent event );
    bool keyDown( ci::app::KeyEvent event );
    bool keyUp( ci::app::KeyEvent event );
    void resize();
    
    int getMouseButton( ci::app::MouseEvent event );
    void initKeyMap();
    Rocket::Core::word getCharacterCode(Rocket::Core::Input::KeyIdentifier key_identifier, int key_modifier_state);
  
    ciLibRocketRenderInterface  mRenderer;
    ciLibRocketSystemInterface  mSystemInterface;
    
    Rocket::Core::Context           *mContext;
    Rocket::Core::ElementDocument   *mDocument;

    ci::signals::scoped_connection  mCbMouseDown, mCbMouseDrag, mCbMouseUp, mCbMouseMove, mCbMouseWheel;
    ci::signals::scoped_connection  mCbKeyDown, mCbKeyUp;
    ci::signals::scoped_connection  mCbResize;
  
    std::map<int, Rocket::Core::Input::KeyIdentifier> mCinderKeyToRocket;

};


#endif
