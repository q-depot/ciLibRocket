#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Vbo.h"
#include "cinder/Rand.h"

#include <Rocket/Core.h>
#include <Rocket/Debugger.h>

#include "ciLibRocketRenderInterface.h"
#include "ciLibRocketSystemInterface.h"


using namespace ci;
using namespace ci::app;
using namespace std;


class BasicSampleApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    ciLibRocketRenderInterface  mRendererInterface;
    ciLibRocketSystemInterface  mSystemInterface;

    Rocket::Core::Context           *mContext;
    Rocket::Core::ElementDocument   *mDocument;
};

void BasicSampleApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1024, 768 );
}

void BasicSampleApp::setup()
{
    mContext = NULL;
    
	Rocket::Core::SetRenderInterface( &mRendererInterface );
	Rocket::Core::SetSystemInterface( &mSystemInterface );
//    mRendererInterface.SetViewport( 1024, 768 );
    
    Rocket::Core::Initialise();
    
	mContext = Rocket::Core::CreateContext( "main", Rocket::Core::Vector2i( 1024, 768 ) );
	if ( mContext == NULL )
    {
		Rocket::Core::Shutdown();
        console() << "no context" << endl;
        exit(-1);
    }
    
	Rocket::Debugger::Initialise( mContext );

    Rocket::Core::String font_names[4];
    font_names[0] = getAssetPath( "Delicious-Roman.otf" ).generic_string().c_str();
    font_names[1] = getAssetPath( "Delicious-Italic.otf" ).generic_string().c_str();
    font_names[2] = getAssetPath( "Delicious-Bold.otf" ).generic_string().c_str();
    font_names[3] = getAssetPath( "Delicious-BoldItalic.otf" ).generic_string().c_str();
    for (int i = 0; i < sizeof(font_names) / sizeof(Rocket::Core::String); i++)
        Rocket::Core::FontDatabase::LoadFontFace( font_names[i] );
    
    
	// Load and show the tutorial document.
    mDocument = mContext->LoadDocument( getAssetPath( "demo.rml" ).generic_string().c_str() );
	if ( mDocument != NULL )
	{
		mDocument->Show();
//		document->RemoveReference();
	}
    
}

void BasicSampleApp::mouseDown( MouseEvent event )
{
}

void BasicSampleApp::update()
{
//	mContext->Update();
}

void BasicSampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    mContext->Render();
}

CINDER_APP_NATIVE( BasicSampleApp, RendererGl )

