
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
//#include "ciLibRocketCustomElement.h"


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
    
    /*

	void update(ofEventArgs& e);
	void update();
	void draw(ofEventArgs& e);

    
	//always load font before calling setup
	void loadFont(string file);
	

	
	void keyPressed( ofKeyEventArgs& e);
	void keyReleased( ofKeyEventArgs& e);
	void mouseMoved( ofMouseEventArgs& e);
	void mouseDragged( ofMouseEventArgs& e);
	void mousePressed( ofMouseEventArgs& e);
	void mouseReleased( ofMouseEventArgs& e);
	void resize( ofResizeEventArgs& e);
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void scrolled(float deltaX, float deltaY);
    
	void resize(int w, int h);
    
	
	void initialiseKeyMap();
	
	void toggleDebugger();
	void showDebugger();
	void hideDebugger();
	
	template <class T>
	void addCustomElement(string tagName){
		ciLibRocketCustomElementHandler::addCustomElement<T>(tagName);
	}
	
	static ciLibRocketDocument* getDocumentFromRocket(Rocket::Core::ElementDocument* doc);
	*/
private:
    
    bool mouseDown( ci::app::MouseEvent event );
    bool mouseUp( ci::app::MouseEvent event );
    bool mouseMove( ci::app::MouseEvent event );
    bool mouseDrag( ci::app::MouseEvent event );
    bool mouseWheel( ci::app::MouseEvent event );
    bool keyDown( ci::app::KeyEvent event );
    bool keyUp( ci::app::KeyEvent event );
    void resize();
    
    int getKeyModifier( ci::app::MouseEvent event );
    int getMouseButton( ci::app::MouseEvent event );


    /*
	void OnDocumentLoad(Rocket::Core::ElementDocument* document);
	void OnElementCreate(Rocket::Core::Element* element);
	
    
	int getKeyModifier();
	bool keyState[OFX_LIBROCKET_MAX_KEYS];
    
	static std::map<Rocket::Core::ElementDocument*, ciLibRocketDocument*> rocketDocuments;
    */
    
    ciLibRocketRenderInterface  mRenderer;
    ciLibRocketSystemInterface  mSystemInterface;
    
    Rocket::Core::Context           *mContext;
    Rocket::Core::ElementDocument   *mDocument;
    
    //    app::App *mApp;
    ci::signals::scoped_connection  mCbMouseDown, mCbMouseDrag, mCbMouseUp, mCbMouseMove, mCbMouseWheel;
    ci::signals::scoped_connection  mCbKeyDown, mCbKeyUp;
    ci::signals::scoped_connection  mCbResize;
};


#endif
