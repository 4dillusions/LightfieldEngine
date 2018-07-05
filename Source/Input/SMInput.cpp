#include "SMInput.h"
#include "FApp.h"
#include "..\\Audio\\SMAudio.h"

using namespace Osp::App;
using namespace SMEngine::Audio;

namespace SMEngine { namespace Input
{
	SMInput *SMInput::instance = nullptr;

	SMInput::SMInput() : TouchPressedEvent(&SMITouchPressedEventHandler::TouchPressed), TouchReleasedEvent(&SMITouchReleasedEventHandler::TouchReleased),
	    KeyPressedEvent(&SMIKeyPressedEventHandler::KeyPressed)
	{
		frame = Application::GetInstance()->GetAppFrame()->GetFrame();
		frame->AddTouchEventListener(*this);
		frame->AddKeyEventListener(*this);
	}

	SMInput::~SMInput()
	{
		//frame->RemoveTouchEventListener(*this);
	}

	SMInput *SMInput::Instance()
	{
		return instance;
	}

	void SMInput::CreateInstance()
	{
		if (instance == nullptr)
			instance = new SMInput();
	}

	void SMInput::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void SMInput::OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{ }

	void SMInput::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{ }

	void SMInput::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{ }

	void SMInput::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{ }

	void SMInput::OnTouchMoved(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{ }

	void SMInput::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
		touchPressedArgs.x = currentPosition.x;
		touchPressedArgs.y = currentPosition.y;

		TouchPressedEvent(touchPressedArgs);
	}

	void SMInput::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
	{
		touchReleasedArgs.x = currentPosition.x;
		touchReleasedArgs.y = currentPosition.y;

		TouchReleasedEvent(touchReleasedArgs);
	}

	void SMInput::OnKeyLongPressed (const Control &source, KeyCode keyCode)
	{ }

	void SMInput::OnKeyPressed (const Control &source, KeyCode keyCode)
	{
		int musicVolume = 0;

		switch(keyCode)
		{
			case KEY_SIDE_UP: //hangerõ fel
				musicVolume = SMAudio::Instance()->GetSoundVolume(SMAudio::MUSIC);
				musicVolume += 10;
				SMAudio::Instance()->SetSoundVolume(SMAudio::MUSIC, musicVolume);

				keyPressedArgs.key = KEY_SOUND_UP;
				KeyPressedEvent(keyPressedArgs);
				break;

			case KEY_SIDE_DOWN: //hangerõ le
				musicVolume = SMAudio::Instance()->GetSoundVolume(SMAudio::MUSIC);
				musicVolume -= 10;
				SMAudio::Instance()->SetSoundVolume(SMAudio::MUSIC, musicVolume);

				keyPressedArgs.key = KEY_SOUND_DOWN;
				KeyPressedEvent(keyPressedArgs);
				break;
		}
	}

	void SMInput::OnKeyReleased (const Control &source, KeyCode keyCode)
	{ }
};};
