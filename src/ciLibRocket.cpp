

#include "ciLibRocket.h"
#include "ciLibRocketElementInstancer.h"


using namespace ci;
using namespace ci::app;
using namespace std;

template <typename T> int getKeyModifier(T event)
{
  int ret = 0;
  if (event.isControlDown())
    ret |= Rocket::Core::Input::KM_CTRL;
  if (event.isShiftDown())
    ret |= Rocket::Core::Input::KM_SHIFT;
  if (event.isAltDown())
    ret |= Rocket::Core::Input::KM_ALT;
  if (event.isMetaDown())
    ret |= Rocket::Core::Input::KM_META;
  // TODO: Caps, Num, and Scroll lock
  return ret;
}

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
    
    Rocket::Core::ElementInstancer* custom_instancer = new Rocket::Core::ElementInstancerGeneric< ciLibRocketSlider >();
    Rocket::Core::Factory::RegisterElementInstancer( "slider", custom_instancer );
    custom_instancer->RemoveReference();
  
    mContext = NULL;
    mContext = Rocket::Core::CreateContext( "main", Rocket::Core::Vector2i( 1024, 768 ) );

    if ( mContext == NULL )
    {
		Rocket::Core::Shutdown();
        console() << "no context" << endl;
        exit(-1);
    }
    
	Rocket::Debugger::Initialise( mContext );
    
    Rocket::Core::FontDatabase::LoadFontFace( getAssetPath( "Delicious-Roman.otf" ).generic_string().c_str() );
    
    loadDocument( getAssetPath( "test01.rml" ) );
    
    Rocket::Core::RegisterPlugin(this);
  
	registerCallbacks();
  initKeyMap();
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
    auto i = mCinderKeyToRocket.find(event.getCode());
    if (i != mCinderKeyToRocket.end())
    {
        //    printf("keydown: cinder: %d, rocket: %d\n", i->first, i->second);
        int modifierState = getKeyModifier(event);
        mContext->ProcessKeyDown(i->second, modifierState);
        Rocket::Core::word character = getCharacterCode(i->second, modifierState);
        if (character > 0)
            mContext->ProcessTextInput(character);
    }
    return false;
}

bool ciLibRocket::keyUp( KeyEvent event )
{
    auto i = mCinderKeyToRocket.find(event.getCode());
    if (i != mCinderKeyToRocket.end())
    {
        mContext->ProcessKeyUp(i->second, getKeyModifier(event));
    }
    return false;
}


void ciLibRocket::resize()
{
    mContext->SetDimensions( Rocket::Core::Vector2i( getWindowWidth(), getWindowHeight() ) );
}


int ciLibRocket::getMouseButton( MouseEvent event )
{
    if ( event.isLeftDown() )       return 0;
    else if ( event.isRightDown() ) return 1;
    else                            return 2;
}

void ciLibRocket::initKeyMap()
{
  mCinderKeyToRocket[KeyEvent::KEY_BACKSPACE] = Rocket::Core::Input::KI_BACK;
  mCinderKeyToRocket[KeyEvent::KEY_TAB] = Rocket::Core::Input::KI_TAB;
  mCinderKeyToRocket[KeyEvent::KEY_CLEAR] = Rocket::Core::Input::KI_CLEAR;
  mCinderKeyToRocket[KeyEvent::KEY_RETURN] = Rocket::Core::Input::KI_RETURN;
  mCinderKeyToRocket[KeyEvent::KEY_PAUSE] = Rocket::Core::Input::KI_PAUSE;
  mCinderKeyToRocket[KeyEvent::KEY_ESCAPE] = Rocket::Core::Input::KI_ESCAPE;
  mCinderKeyToRocket[KeyEvent::KEY_SPACE] = Rocket::Core::Input::KI_SPACE;
  mCinderKeyToRocket[KeyEvent::KEY_QUOTE] = Rocket::Core::Input::KI_OEM_7;
  mCinderKeyToRocket[KeyEvent::KEY_PLUS] = Rocket::Core::Input::KI_OEM_PLUS;
  mCinderKeyToRocket[KeyEvent::KEY_COMMA] = Rocket::Core::Input::KI_OEM_COMMA;
  mCinderKeyToRocket[KeyEvent::KEY_MINUS] = Rocket::Core::Input::KI_OEM_MINUS;
  mCinderKeyToRocket[KeyEvent::KEY_PERIOD] = Rocket::Core::Input::KI_OEM_PERIOD;
  mCinderKeyToRocket[KeyEvent::KEY_SLASH] = Rocket::Core::Input::KI_OEM_2;
  mCinderKeyToRocket[KeyEvent::KEY_0] = Rocket::Core::Input::KI_0;
  mCinderKeyToRocket[KeyEvent::KEY_1] = Rocket::Core::Input::KI_1;
  mCinderKeyToRocket[KeyEvent::KEY_2] = Rocket::Core::Input::KI_2;
  mCinderKeyToRocket[KeyEvent::KEY_3] = Rocket::Core::Input::KI_3;
  mCinderKeyToRocket[KeyEvent::KEY_4] = Rocket::Core::Input::KI_4;
  mCinderKeyToRocket[KeyEvent::KEY_5] = Rocket::Core::Input::KI_5;
  mCinderKeyToRocket[KeyEvent::KEY_6] = Rocket::Core::Input::KI_6;
  mCinderKeyToRocket[KeyEvent::KEY_7] = Rocket::Core::Input::KI_7;
  mCinderKeyToRocket[KeyEvent::KEY_8] = Rocket::Core::Input::KI_8;
  mCinderKeyToRocket[KeyEvent::KEY_9] = Rocket::Core::Input::KI_9;
  mCinderKeyToRocket[KeyEvent::KEY_SEMICOLON] = Rocket::Core::Input::KI_OEM_1;
  mCinderKeyToRocket[KeyEvent::KEY_EQUALS] = Rocket::Core::Input::KI_OEM_PLUS;
  mCinderKeyToRocket[KeyEvent::KEY_LEFTBRACKET] = Rocket::Core::Input::KI_OEM_4;
  mCinderKeyToRocket[KeyEvent::KEY_BACKSLASH] = Rocket::Core::Input::KI_OEM_5;
  mCinderKeyToRocket[KeyEvent::KEY_RIGHTBRACKET] = Rocket::Core::Input::KI_OEM_6;
  mCinderKeyToRocket[KeyEvent::KEY_BACKQUOTE] = Rocket::Core::Input::KI_OEM_3;
  mCinderKeyToRocket[KeyEvent::KEY_a] = Rocket::Core::Input::KI_A;
  mCinderKeyToRocket[KeyEvent::KEY_b] = Rocket::Core::Input::KI_B;
  mCinderKeyToRocket[KeyEvent::KEY_c] = Rocket::Core::Input::KI_C;
  mCinderKeyToRocket[KeyEvent::KEY_d] = Rocket::Core::Input::KI_D;
  mCinderKeyToRocket[KeyEvent::KEY_e] = Rocket::Core::Input::KI_E;
  mCinderKeyToRocket[KeyEvent::KEY_f] = Rocket::Core::Input::KI_F;
  mCinderKeyToRocket[KeyEvent::KEY_g] = Rocket::Core::Input::KI_G;
  mCinderKeyToRocket[KeyEvent::KEY_h] = Rocket::Core::Input::KI_H;
  mCinderKeyToRocket[KeyEvent::KEY_i] = Rocket::Core::Input::KI_I;
  mCinderKeyToRocket[KeyEvent::KEY_j] = Rocket::Core::Input::KI_J;
  mCinderKeyToRocket[KeyEvent::KEY_k] = Rocket::Core::Input::KI_K;
  mCinderKeyToRocket[KeyEvent::KEY_l] = Rocket::Core::Input::KI_L;
  mCinderKeyToRocket[KeyEvent::KEY_m] = Rocket::Core::Input::KI_M;
  mCinderKeyToRocket[KeyEvent::KEY_n] = Rocket::Core::Input::KI_N;
  mCinderKeyToRocket[KeyEvent::KEY_o] = Rocket::Core::Input::KI_O;
  mCinderKeyToRocket[KeyEvent::KEY_p] = Rocket::Core::Input::KI_P;
  mCinderKeyToRocket[KeyEvent::KEY_q] = Rocket::Core::Input::KI_Q;
  mCinderKeyToRocket[KeyEvent::KEY_r] = Rocket::Core::Input::KI_R;
  mCinderKeyToRocket[KeyEvent::KEY_s] = Rocket::Core::Input::KI_S;
  mCinderKeyToRocket[KeyEvent::KEY_t] = Rocket::Core::Input::KI_T;
  mCinderKeyToRocket[KeyEvent::KEY_u] = Rocket::Core::Input::KI_U;
  mCinderKeyToRocket[KeyEvent::KEY_v] = Rocket::Core::Input::KI_V;
  mCinderKeyToRocket[KeyEvent::KEY_w] = Rocket::Core::Input::KI_W;
  mCinderKeyToRocket[KeyEvent::KEY_x] = Rocket::Core::Input::KI_X;
  mCinderKeyToRocket[KeyEvent::KEY_y] = Rocket::Core::Input::KI_Y;
  mCinderKeyToRocket[KeyEvent::KEY_z] = Rocket::Core::Input::KI_Z;
  mCinderKeyToRocket[KeyEvent::KEY_DELETE] = Rocket::Core::Input::KI_DELETE;
  
  mCinderKeyToRocket[KeyEvent::KEY_KP0] = Rocket::Core::Input::KI_NUMPAD0;
  mCinderKeyToRocket[KeyEvent::KEY_KP1] = Rocket::Core::Input::KI_NUMPAD1;
  mCinderKeyToRocket[KeyEvent::KEY_KP2] = Rocket::Core::Input::KI_NUMPAD2;
  mCinderKeyToRocket[KeyEvent::KEY_KP3] = Rocket::Core::Input::KI_NUMPAD3;
  mCinderKeyToRocket[KeyEvent::KEY_KP4] = Rocket::Core::Input::KI_NUMPAD4;
  mCinderKeyToRocket[KeyEvent::KEY_KP5] = Rocket::Core::Input::KI_NUMPAD5;
  mCinderKeyToRocket[KeyEvent::KEY_KP6] = Rocket::Core::Input::KI_NUMPAD6;
  mCinderKeyToRocket[KeyEvent::KEY_KP7] = Rocket::Core::Input::KI_NUMPAD7;
  mCinderKeyToRocket[KeyEvent::KEY_KP8] = Rocket::Core::Input::KI_NUMPAD8;
  mCinderKeyToRocket[KeyEvent::KEY_KP9] = Rocket::Core::Input::KI_NUMPAD9;
  
  mCinderKeyToRocket[KeyEvent::KEY_KP_PERIOD] = Rocket::Core::Input::KI_DECIMAL;
  mCinderKeyToRocket[KeyEvent::KEY_KP_DIVIDE] = Rocket::Core::Input::KI_DIVIDE;
  mCinderKeyToRocket[KeyEvent::KEY_KP_MULTIPLY] = Rocket::Core::Input::KI_MULTIPLY;
  mCinderKeyToRocket[KeyEvent::KEY_KP_MINUS] = Rocket::Core::Input::KI_OEM_MINUS;
  mCinderKeyToRocket[KeyEvent::KEY_KP_PLUS] = Rocket::Core::Input::KI_ADD;
  mCinderKeyToRocket[KeyEvent::KEY_KP_ENTER] = Rocket::Core::Input::KI_NUMPADENTER;
  mCinderKeyToRocket[KeyEvent::KEY_KP_EQUALS] = Rocket::Core::Input::KI_OEM_NEC_EQUAL;
  
  mCinderKeyToRocket[KeyEvent::KEY_UP] = Rocket::Core::Input::KI_UP;
  mCinderKeyToRocket[KeyEvent::KEY_DOWN] = Rocket::Core::Input::KI_DOWN;
  mCinderKeyToRocket[KeyEvent::KEY_RIGHT] = Rocket::Core::Input::KI_RIGHT;
  mCinderKeyToRocket[KeyEvent::KEY_LEFT] = Rocket::Core::Input::KI_LEFT;
  mCinderKeyToRocket[KeyEvent::KEY_INSERT] = Rocket::Core::Input::KI_INSERT;
  mCinderKeyToRocket[KeyEvent::KEY_HOME] = Rocket::Core::Input::KI_HOME;
  mCinderKeyToRocket[KeyEvent::KEY_END] = Rocket::Core::Input::KI_END;
  mCinderKeyToRocket[KeyEvent::KEY_PAGEUP] = Rocket::Core::Input::KI_PRIOR;
  mCinderKeyToRocket[KeyEvent::KEY_PAGEDOWN] = Rocket::Core::Input::KI_NEXT;
  
  mCinderKeyToRocket[KeyEvent::KEY_F1] = Rocket::Core::Input::KI_F1;
  mCinderKeyToRocket[KeyEvent::KEY_F2] = Rocket::Core::Input::KI_F2;
  mCinderKeyToRocket[KeyEvent::KEY_F3] = Rocket::Core::Input::KI_F3;
  mCinderKeyToRocket[KeyEvent::KEY_F4] = Rocket::Core::Input::KI_F4;
  mCinderKeyToRocket[KeyEvent::KEY_F5] = Rocket::Core::Input::KI_F5;
  mCinderKeyToRocket[KeyEvent::KEY_F6] = Rocket::Core::Input::KI_F6;
  mCinderKeyToRocket[KeyEvent::KEY_F7] = Rocket::Core::Input::KI_F7;
  mCinderKeyToRocket[KeyEvent::KEY_F8] = Rocket::Core::Input::KI_F8;
  mCinderKeyToRocket[KeyEvent::KEY_F9] = Rocket::Core::Input::KI_F9;
  mCinderKeyToRocket[KeyEvent::KEY_F10] = Rocket::Core::Input::KI_F10;
  mCinderKeyToRocket[KeyEvent::KEY_F11] = Rocket::Core::Input::KI_F11;
  mCinderKeyToRocket[KeyEvent::KEY_F12] = Rocket::Core::Input::KI_F12;
  mCinderKeyToRocket[KeyEvent::KEY_F13] = Rocket::Core::Input::KI_F13;
  mCinderKeyToRocket[KeyEvent::KEY_F14] = Rocket::Core::Input::KI_F14;
  mCinderKeyToRocket[KeyEvent::KEY_F15] = Rocket::Core::Input::KI_F15;
  
  mCinderKeyToRocket[KeyEvent::KEY_NUMLOCK] = Rocket::Core::Input::KI_NUMLOCK;
  mCinderKeyToRocket[KeyEvent::KEY_CAPSLOCK] = Rocket::Core::Input::KI_CAPITAL;
  mCinderKeyToRocket[KeyEvent::KEY_SCROLLOCK] = Rocket::Core::Input::KI_SCROLL;
  mCinderKeyToRocket[KeyEvent::KEY_RSHIFT] = Rocket::Core::Input::KI_RSHIFT;
  mCinderKeyToRocket[KeyEvent::KEY_LSHIFT] = Rocket::Core::Input::KI_LSHIFT;
  mCinderKeyToRocket[KeyEvent::KEY_RCTRL] = Rocket::Core::Input::KI_RCONTROL;
  mCinderKeyToRocket[KeyEvent::KEY_LCTRL] = Rocket::Core::Input::KI_LCONTROL;
  
  mCinderKeyToRocket[KeyEvent::KEY_RMETA] = Rocket::Core::Input::KI_RMETA;
  mCinderKeyToRocket[KeyEvent::KEY_LMETA] = Rocket::Core::Input::KI_LMETA;
  
  mCinderKeyToRocket[KeyEvent::KEY_HELP] = Rocket::Core::Input::KI_HELP;
  mCinderKeyToRocket[KeyEvent::KEY_PRINT] = Rocket::Core::Input::KI_SNAPSHOT;
  mCinderKeyToRocket[KeyEvent::KEY_MENU] = Rocket::Core::Input::KI_LMENU;
  mCinderKeyToRocket[KeyEvent::KEY_POWER] = Rocket::Core::Input::KI_POWER;
}

char ascii_map[4][51] =
{
  // shift off and capslock off
  {
		0,
		' ',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z',
		';',
		'=',
		',',
		'-',
		'.',
		'/',
		'`',
		'[',
		'\\',
		']',
		'\'',
		0,
		0
	},
  
	// shift on and capslock off
  {
		0,
		' ',
		')',
		'!',
		'@',
		'#',
		'$',
		'%',
		'^',
		'&',
		'*',
		'(',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		':',
		'+',
		'<',
		'_',
		'>',
		'?',
		'~',
		'{',
		'|',
		'}',
		'"',
		0,
		0
	},
  
	// shift on and capslock on
  {
		0,
		' ',
		')',
		'!',
		'@',
		'#',
		'$',
		'%',
		'^',
		'&',
		'*',
		'(',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z',
		':',
		'+',
		'<',
		'_',
		'>',
		'?',
		'~',
		'{',
		'|',
		'}',
		'"',
		0,
		0
	},
  
	// shift off and capslock on
  {
		0,
		' ',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		';',
		'=',
		',',
		'-',
		'.',
		'/',
		'`',
		'[',
		'\\',
		']',
		'\'',
		0,
		0
	}
};

char keypad_map[2][18] =
{
	{
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'\n',
		'*',
		'+',
		0,
		'-',
		'.',
		'/',
		'='
	},
  
	{
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		'\n',
		'*',
		'+',
		0,
		'-',
		0,
		'/',
		'='
	}
};

// Returns the character code for a key identifer / key modifier combination.
Rocket::Core::word ciLibRocket::getCharacterCode(Rocket::Core::Input::KeyIdentifier key_identifier, int key_modifier_state)
{
	// Check if we have a keycode capable of generating characters on the main keyboard (ie, not on the numeric
	// keypad; that is dealt with below).
	if (key_identifier <= Rocket::Core::Input::KI_OEM_102)
	{
		// Get modifier states
		bool shift = (key_modifier_state & Rocket::Core::Input::KM_SHIFT) > 0;
		bool capslock = (key_modifier_state & Rocket::Core::Input::KM_CAPSLOCK) > 0;
    
		// Return character code based on identifier and modifiers
		if (shift && !capslock)
			return ascii_map[1][key_identifier];
    
		if (shift && capslock)
			return ascii_map[2][key_identifier];
    
		if (!shift && capslock)
			return ascii_map[3][key_identifier];
    
		return ascii_map[0][key_identifier];
	}
  
	// Check if we have a keycode from the numeric keypad.
	else if (key_identifier <= Rocket::Core::Input::KI_OEM_NEC_EQUAL)
	{
		if (key_modifier_state & Rocket::Core::Input::KM_NUMLOCK)
			return keypad_map[0][key_identifier - Rocket::Core::Input::KI_NUMPAD0];
		else
			return keypad_map[1][key_identifier - Rocket::Core::Input::KI_NUMPAD0];
	}
  
	else if (key_identifier == Rocket::Core::Input::KI_RETURN)
		return '\n';
  
	return 0;
}