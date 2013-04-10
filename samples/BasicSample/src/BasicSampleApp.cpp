

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ciLibRocket.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class BasicSampleApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();
    void keyDown( KeyEvent event );
    
    ciLibRocket                 mRocket;
};

void BasicSampleApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1024, 768 );
}

void BasicSampleApp::setup()
{
    mRocket.setup();
}

void BasicSampleApp::update()
{
    
    mRocket.update();
}

void BasicSampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    mRocket.render();
}


void BasicSampleApp::keyDown( KeyEvent event )
{
    char c = event.getChar();
    
    if ( event.isAltDown() )
    {
        if ( c == 'd' )
            mRocket.toggleDebugger();
    }
    
}


CINDER_APP_NATIVE( BasicSampleApp, RendererGl )

