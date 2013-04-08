

#include "ciLibRocket.h"

//#include "ciLibRocketSlider.h"

using namespace ci;
using namespace ci::app;
using namespace std;


ciLibRocket::~ciLibRocket()
{
    unregisterCallbacks();
}


void ciLibRocket::setup()
{
	Rocket::Core::SetRenderInterface( &mRenderer );
	Rocket::Core::SetSystemInterface( &mSystemInterface );
    
    Rocket::Core::Initialise();
    Rocket::Controls::Initialise();
    
    mContext = NULL;
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
    
    
    loadDocument( getAssetPath( "test01.rml" ) );
    
    
    Rocket::Core::RegisterPlugin(this);
  
	registerCallbacks();
}

void ciLibRocket::registerCallbacks()
{
    ci::app::WindowRef window = app::App::get()->getWindow();
    
	mCbMouseDown    = window->getSignalMouseDown().connect( std::bind( &ciLibRocket::mouseDown, this, std::_1 ) );
	mCbMouseUp      = window->getSignalMouseUp().connect( std::bind( &ciLibRocket::mouseUp, this, std::_1 ) );
	mCbMouseDrag    = window->getSignalMouseDrag().connect( std::bind( &ciLibRocket::mouseDrag, this, std::_1 ) );
	mCbMouseMove    = window->getSignalMouseMove().connect( std::bind( &ciLibRocket::mouseMove, this, std::_1 ) );
	mCbMouseWheel   = window->getSignalMouseWheel().connect( std::bind( &ciLibRocket::mouseWheel, this, std::_1 ) );
	mCbKeyDown      = window->getSignalKeyDown().connect( std::bind( &ciLibRocket::keyDown, this, std::_1 ) );
	mCbKeyUp        = window->getSignalKeyUp().connect( std::bind( &ciLibRocket::keyUp, this, std::_1 ) );
    mCbResize       = window->getSignalResize().connect( std::bind( &ciLibRocket::resize, this ) );
    
//    ofAddListener(ofEvents().windowResized, this, &ciLibRocket::resize);
}

void ciLibRocket::unregisterCallbacks()
{
    mCbMouseDown.disconnect();
	mCbMouseUp.disconnect();
	mCbMouseDrag.disconnect();
	mCbMouseMove.disconnect();
	mCbMouseWheel.disconnect();
	mCbKeyDown.disconnect();
	mCbKeyUp.disconnect();
   	mCbResize.disconnect();
}

void ciLibRocket::loadDocument( fs::path filePath )
{
    mDocument = mContext->LoadDocument( filePath.generic_string().c_str() );
	if ( mDocument != NULL )
	{
		mDocument->Show();
        mDocument->RemoveReference();
	}
}

bool ciLibRocket::mouseDown( MouseEvent event )
{        
 	mContext->ProcessMouseButtonDown( getMouseButton( event ), getKeyModifier( event ) );
    return false;
}


bool ciLibRocket::mouseUp( MouseEvent event )
{
	mContext->ProcessMouseButtonUp( getMouseButton( event ), getKeyModifier( event ) );
    return false;
}


bool ciLibRocket::mouseMove( MouseEvent event )
{
    Vec2i pos = event.getPos();
	mContext->ProcessMouseMove( pos.x, pos.y, getKeyModifier( event ) );
    return false;
}


bool ciLibRocket::mouseDrag( MouseEvent event )
{
    Vec2i pos = event.getPos();
	mContext->ProcessMouseMove( pos.x, pos.y, getKeyModifier( event ) );
    return false;
}


bool ciLibRocket::mouseWheel( MouseEvent event )
{
    mContext->ProcessMouseWheel( event.getWheelIncrement(), getKeyModifier( event ) );
    return false;
}


bool ciLibRocket::keyDown( KeyEvent event )
{
//	if(key < OFX_LIBROCKET_MAX_KEYS)
//		keyState[key] = true;
//	Rocket::Core::Input::KeyIdentifier key_identifier = key_identifier_map[key];
//	if (key_identifier != Rocket::Core::Input::KI_UNKNOWN)
//		context->ProcessKeyDown(key_identifier, 0);
//	if(key != OF_KEY_BACKSPACE && key != OF_KEY_DEL && key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_DOWN && key != OF_KEY_UP && key != OF_KEY_RETURN)
//		context->ProcessTextInput(key);
    
    return false;
}


bool ciLibRocket::keyUp( KeyEvent event )
{
    //    if(key < OFX_LIBROCKET_MAX_KEYS)
    //    keyState[key] = false;
    //	Rocket::Core::Input::KeyIdentifier key_identifier = key_identifier_map[key];
//    mContext->ProcessKeyUp( key_identifier, getKeyModifier());
    return false;
}


void ciLibRocket::resize()
{
    mContext->SetDimensions( Rocket::Core::Vector2i( getWindowWidth(), getWindowHeight() ) );
}


int ciLibRocket::getKeyModifier( MouseEvent event )
{
    int keyModifier = 0;
    if ( event.isShiftDown() )      keyModifier |= Rocket::Core::Input::KM_SHIFT;
    if ( event.isControlDown() )	keyModifier |= Rocket::Core::Input::KM_CTRL;
    if ( event.isAltDown() )        keyModifier |= Rocket::Core::Input::KM_ALT;
    
    return keyModifier;
}


int ciLibRocket::getMouseButton( MouseEvent event )
{
    if ( event.isLeftDown() )       return 0;
    else if ( event.isRightDown() ) return 1;
    else                            return 2;
}






//void ciLibRocket::OnDocumentLoad(ElementDocument* document)
//{
//	/*if(rocketDocuments.find(document) != rocketDocuments.end())
//     return;
//     
//     ciLibRocketDocument* doc =  new ciLibRocketDocument(document);
//     rocketDocuments[document] = doc;*/
//}
//
//void ciLibRocket::OnElementCreate(Rocket::Core::Element* element)
//{
//	/*
//     ciLibRocketDocument* doc = getDocumentFromRocket(element->GetOwnerDocument());
//     ciLibRocketElement* el = new ciLibRocketElement(element);
//     doc->addElement(el);
//     */
//}
//
//ciLibRocketDocument* ciLibRocket::getDocumentFromRocket(Rocket::Core::ElementDocument* doc)
//{
//	if(rocketDocuments.find(doc) != rocketDocuments.end()){
//		return rocketDocuments[doc];
//	}else{
//		rocketDocuments[doc] = new ciLibRocketDocument(doc);
//		return rocketDocuments[doc];
//	}
//	return NULL;
//}
//
//void ciLibRocket::toggleDebugger()
//{
//	Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
//}
//
//void ciLibRocket::hideDebugger()
//{
//	Rocket::Debugger::SetVisible(false);
//}
//
//void ciLibRocket::showDebugger()
//{
//	Rocket::Debugger::SetVisible(true);
//}
//
//void ciLibRocket::update()
//{
//	context->Update();
//}
//
//void ciLibRocket::draw()
//{
//	ofEnableAlphaBlending();
//	context->Render();
//	ofDisableAlphaBlending();
//}
//
//void ciLibRocket::mouseMoved(int x, int y)
//{
//	context->ProcessMouseMove(x, y, getKeyModifier());
//}
//
//void ciLibRocket::mousePressed(int x, int y, int button)
//{
//	context->ProcessMouseButtonDown(button, getKeyModifier());
//}
//
//void ciLibRocket::mouseDragged(int x, int y, int button)
//{
//	context->ProcessMouseMove(x, y, getKeyModifier());
//}
//
//void ciLibRocket::mouseReleased(int x, int y, int button)
//{
//	context->ProcessMouseButtonUp(button, getKeyModifier());
//}
//
//void ciLibRocket::scrolled(float deltaX, float deltaY)
//{
//	context->ProcessMouseWheel(-deltaY, getKeyModifier());
//}
//
//void ciLibRocket::keyPressed(int key)
//{
//	if(key < OFX_LIBROCKET_MAX_KEYS)
//		keyState[key] = true;
//	Rocket::Core::Input::KeyIdentifier key_identifier = key_identifier_map[key];
//	if (key_identifier != Rocket::Core::Input::KI_UNKNOWN)
//		context->ProcessKeyDown(key_identifier, 0);
//	if(key != OF_KEY_BACKSPACE && key != OF_KEY_DEL && key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_DOWN && key != OF_KEY_UP && key != OF_KEY_RETURN)
//		context->ProcessTextInput(key);
//}
//
//void ciLibRocket::keyReleased(int key)
//{
//	if(key < OFX_LIBROCKET_MAX_KEYS)
//		keyState[key] = false;
//	Rocket::Core::Input::KeyIdentifier key_identifier = key_identifier_map[key];
//	context->ProcessKeyUp(key_identifier, getKeyModifier());
//}
//
//void ciLibRocket::resize(int w, int h)
//{
//	context->SetDimensions(Vector2i(w, h));
//}
//

//void ciLibRocket::keyPressed(ofKeyEventArgs& e)
//{
//	keyPressed(e.key);
//}
//
//void ciLibRocket::keyReleased(ofKeyEventArgs& e)
//{
//	keyReleased(e.key);
//}
//
//
//void ciLibRocket::mouseDragged(ofMouseEventArgs& e)
//{
//	mouseDragged(e.x, e.y, e.button);
//}
//
//void ciLibRocket::mouseMoved(ofMouseEventArgs& e)
//{
//	mouseMoved(e.x, e.y);
//}
//
//void ciLibRocket::mousePressed(ofMouseEventArgs& e)
//{
//	mousePressed(e.x, e.y, e.button);
//}
//
//void ciLibRocket::mouseReleased(ofMouseEventArgs& e)
//{
//	mouseReleased(e.x, e.y, e.button);
//}
//
//void ciLibRocket::resize(ofResizeEventArgs& e)
//{
//	resize(e.width, e.height);
//}
//
//
//void ciLibRocket::initialiseKeyMap()
//{
//	memset(key_identifier_map, sizeof(key_identifier_map), 0);
//	key_identifier_map['a'] = Rocket::Core::Input::KI_A;
//	key_identifier_map['s'] = Rocket::Core::Input::KI_S;
//	key_identifier_map['d'] = Rocket::Core::Input::KI_D;
//	key_identifier_map['f'] = Rocket::Core::Input::KI_F;
//	key_identifier_map['h'] = Rocket::Core::Input::KI_H;
//	key_identifier_map['g'] = Rocket::Core::Input::KI_G;
//	key_identifier_map['z'] = Rocket::Core::Input::KI_Z;
//	key_identifier_map['x'] = Rocket::Core::Input::KI_X;
//	key_identifier_map['c'] = Rocket::Core::Input::KI_C;
//	key_identifier_map['v'] = Rocket::Core::Input::KI_V;
//	key_identifier_map['b'] = Rocket::Core::Input::KI_B;
//	key_identifier_map['q'] = Rocket::Core::Input::KI_Q;
//	key_identifier_map['w'] = Rocket::Core::Input::KI_W;
//	key_identifier_map['e'] = Rocket::Core::Input::KI_E;
//	key_identifier_map['r'] = Rocket::Core::Input::KI_R;
//	key_identifier_map['y'] = Rocket::Core::Input::KI_Y;
//	key_identifier_map['t'] = Rocket::Core::Input::KI_T;
//	key_identifier_map['1'] = Rocket::Core::Input::KI_1;
//	key_identifier_map['2'] = Rocket::Core::Input::KI_2;
//	key_identifier_map['3'] = Rocket::Core::Input::KI_3;
//	key_identifier_map['4'] = Rocket::Core::Input::KI_4;
//	key_identifier_map['6'] = Rocket::Core::Input::KI_6;
//	key_identifier_map['5'] = Rocket::Core::Input::KI_5;
//	key_identifier_map['+'] = Rocket::Core::Input::KI_OEM_PLUS;
//	key_identifier_map['9'] = Rocket::Core::Input::KI_9;
//	key_identifier_map['7'] = Rocket::Core::Input::KI_7;
//	key_identifier_map['-'] = Rocket::Core::Input::KI_OEM_MINUS;
//	key_identifier_map['8'] = Rocket::Core::Input::KI_8;
//	key_identifier_map['0'] = Rocket::Core::Input::KI_0;
//	key_identifier_map[0x1E] = Rocket::Core::Input::KI_OEM_6;
//	key_identifier_map[0x1F] = Rocket::Core::Input::KI_O;
//	key_identifier_map[0x20] = Rocket::Core::Input::KI_U;
//	key_identifier_map[0x21] = Rocket::Core::Input::KI_OEM_4;
//	key_identifier_map[0x22] = Rocket::Core::Input::KI_I;
//	key_identifier_map[0x23] = Rocket::Core::Input::KI_P;
//	key_identifier_map[OF_KEY_RETURN] = Rocket::Core::Input::KI_RETURN;
//	key_identifier_map[0x25] = Rocket::Core::Input::KI_L;
//	key_identifier_map[0x26] = Rocket::Core::Input::KI_J;
//	key_identifier_map[0x27] = Rocket::Core::Input::KI_OEM_7;
//	key_identifier_map[0x28] = Rocket::Core::Input::KI_K;
//	key_identifier_map[0x29] = Rocket::Core::Input::KI_OEM_1;
//	key_identifier_map[0x2A] = Rocket::Core::Input::KI_OEM_5;
//	key_identifier_map[0x2B] = Rocket::Core::Input::KI_OEM_COMMA;
//	key_identifier_map[0x2C] = Rocket::Core::Input::KI_OEM_2;
//	key_identifier_map[0x2D] = Rocket::Core::Input::KI_N;
//	key_identifier_map[0x2E] = Rocket::Core::Input::KI_M;
//	key_identifier_map[0x2F] = Rocket::Core::Input::KI_OEM_PERIOD;
//	key_identifier_map[9] = Rocket::Core::Input::KI_TAB;
//	key_identifier_map[' '] = Rocket::Core::Input::KI_SPACE;
//	key_identifier_map[0x32] = Rocket::Core::Input::KI_OEM_3;
//	key_identifier_map[OF_KEY_BACKSPACE] = Rocket::Core::Input::KI_BACK;
//	key_identifier_map[0x35] = Rocket::Core::Input::KI_ESCAPE;
//	key_identifier_map[0x37] = Rocket::Core::Input::KI_LMETA;
//	key_identifier_map[0x38] = Rocket::Core::Input::KI_LSHIFT;
//	key_identifier_map[0x39] = Rocket::Core::Input::KI_CAPITAL;
//	key_identifier_map[0x3A] = Rocket::Core::Input::KI_LMENU;
//	key_identifier_map[0x3B] = Rocket::Core::Input::KI_LCONTROL;
//	key_identifier_map[0x41] = Rocket::Core::Input::KI_DECIMAL;
//	key_identifier_map[0x43] = Rocket::Core::Input::KI_MULTIPLY;
//	key_identifier_map[0x45] = Rocket::Core::Input::KI_ADD;
//	key_identifier_map[0x4B] = Rocket::Core::Input::KI_DIVIDE;
//	key_identifier_map[0x4C] = Rocket::Core::Input::KI_NUMPADENTER;
//	key_identifier_map[0x4E] = Rocket::Core::Input::KI_SUBTRACT;
//	key_identifier_map[0x51] = Rocket::Core::Input::KI_OEM_PLUS;
//	key_identifier_map[364] = Rocket::Core::Input::KI_NUMPAD0;
//	key_identifier_map[363] = Rocket::Core::Input::KI_NUMPAD1;
//	key_identifier_map[359] = Rocket::Core::Input::KI_NUMPAD2;
//	key_identifier_map[361] = Rocket::Core::Input::KI_NUMPAD3;
//	key_identifier_map[0x56] = Rocket::Core::Input::KI_NUMPAD4;
//	key_identifier_map[0x57] = Rocket::Core::Input::KI_NUMPAD5;
//	key_identifier_map[0x58] = Rocket::Core::Input::KI_NUMPAD6;
//	key_identifier_map[0x59] = Rocket::Core::Input::KI_NUMPAD7;
//	key_identifier_map[0x5B] = Rocket::Core::Input::KI_NUMPAD8;
//	key_identifier_map[0x5C] = Rocket::Core::Input::KI_NUMPAD9;
//	key_identifier_map[0x60] = Rocket::Core::Input::KI_F5;
//	key_identifier_map[0x61] = Rocket::Core::Input::KI_F6;
//	key_identifier_map[0x62] = Rocket::Core::Input::KI_F7;
//	key_identifier_map[0x63] = Rocket::Core::Input::KI_F3;
//	key_identifier_map[0x64] = Rocket::Core::Input::KI_F8;
//	key_identifier_map[0x65] = Rocket::Core::Input::KI_F9;
//	key_identifier_map[0x67] = Rocket::Core::Input::KI_F11;
//	key_identifier_map[0x69] = Rocket::Core::Input::KI_F13;
//	key_identifier_map[0x6B] = Rocket::Core::Input::KI_F14;
//	key_identifier_map[0x6D] = Rocket::Core::Input::KI_F10;
//	key_identifier_map[0x6F] = Rocket::Core::Input::KI_F12;
//	key_identifier_map[0x71] = Rocket::Core::Input::KI_F15;
//	key_identifier_map[OF_KEY_HOME] = Rocket::Core::Input::KI_HOME;
//	key_identifier_map[OF_KEY_PAGE_UP] = Rocket::Core::Input::KI_PRIOR;
//	key_identifier_map[OF_KEY_DEL] = Rocket::Core::Input::KI_DELETE;
//	key_identifier_map[OF_KEY_F4] = Rocket::Core::Input::KI_F4;
//	key_identifier_map[OF_KEY_END] = Rocket::Core::Input::KI_END;
//	key_identifier_map[OF_KEY_F2] = Rocket::Core::Input::KI_F2;
//	key_identifier_map[OF_KEY_PAGE_DOWN] = Rocket::Core::Input::KI_NEXT;
//	key_identifier_map[OF_KEY_F1] = Rocket::Core::Input::KI_F1;
//	key_identifier_map[OF_KEY_LEFT] = Rocket::Core::Input::KI_LEFT;
//	key_identifier_map[OF_KEY_RIGHT] = Rocket::Core::Input::KI_RIGHT;
//	key_identifier_map[OF_KEY_DOWN] = Rocket::Core::Input::KI_DOWN;
//	key_identifier_map[OF_KEY_UP] = Rocket::Core::Input::KI_UP;
//}
//
//int ciLibRocket::getKeyModifier()
//{
//	int key_modifier_state = 0;
//    
//	/*if (keyState[OF_KEY_SHIFT])
//     key_modifier_state |= Rocket::Core::Input::KM_SHIFT;
//     */
//	/*if (keyState[OF_KEY_])
//     key_modifier_state |= Rocket::Core::Input::KM_CAPSLOCK;*/
//    
//	if (keyState[OF_KEY_CTRL])
//		key_modifier_state |= Rocket::Core::Input::KM_CTRL;
//    
//	if (keyState[OF_KEY_ALT])
//		key_modifier_state |= Rocket::Core::Input::KM_ALT;
//    
//	/*if (x_state & Mod2Mask)
//     key_modifier_state |= Rocket::Core::Input::KM_NUMLOCK;*/
//	return key_modifier_state;
//}
