#pragma once

#include "FUiTouch.h"
#include "FUi.h"
#include "FUiControl.h"
#include "FUiIOrientationEventListener.h"
#include "..\\Core\\SMEventArgs.h"
#include "..\\Core\\SMEventHandlers.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace SMEngine::Core;

namespace SMEngine { namespace Input
{
	/*
	Input lekezelése. Touch screen, hardver gombok.
	Az SMInput instance-t AppInitializing-ban kell inicializálni. Kézzel kell felszabadítani is!

	Példa:
	class InputTouchPressedTest : public SMITouchPressedEventHandler, public SMIKeyPressedEventHandler
	{
	public:
		InputTouchPressedTest()
		{
			SMInput::Instance()->TouchPressedEvent += this;
			SMInput::Instance()->KeyPressedEvent += this;
		}

		~InputTouchPressedTest()
		{
			SMInput::Instance()->TouchPressedEvent -= this;
			SMInput::Instance()->KeyPressedEvent -= this;
		}

		override void TouchPressed(const SMTouchEventArgs &args)
		{
			<args.x, args.x>
		}

		override void KeyPressed(const SMKeyboardEventArgs &args)
		{
			args. ....
		}
	};

	Game példa:
	class Game : public SMIAppInitTerminateEventHandler, public SMITouchPressedEventHandler
	{
		override void InitTerminateChanged(const SMAppInitTerminateEventArgs &args);
		override void TouchPressed(const SMTouchEventArgs &args);
	};
	...
		Game::~Game()
		{
			SMInput::Instance()->TouchPressedEvent -= this;
		}

		void Game::InitTerminateChanged(const SMAppInitTerminateEventArgs &args)
		{
			if (args.applicationState == SMAppInitTerminateEventArgs::INITIALIZING)
			{
				SMInput::Instance()->TouchPressedEvent += this;

				CreateSceneGraph();
				LoadContets();
			}
		}

		void Game::TouchPressed(const SMTouchEventArgs &args)
		{
			<args.x, args.x>
		}
	*/
	class SMInput : public ITouchEventListener, public IKeyEventListener
	{
	private:
		SMInput();
		virtual ~SMInput();

		static SMInput *instance;
		Frame *frame;

		SMTouchEventArgs touchPressedArgs, touchReleasedArgs;
		SMKeyboardEventArgs keyPressedArgs;

	public:
		SMEventArgs<SMITouchPressedEventHandler, SMTouchEventArgs> TouchPressedEvent;
		SMEventArgs<SMITouchReleasedEventHandler, SMTouchEventArgs> TouchReleasedEvent;
		SMEventArgs<SMIKeyPressedEventHandler, SMKeyboardEventArgs> KeyPressedEvent;

		static SMInput *Instance();
		static void CreateInstance();
		static void ReleaseInstance();

		//Touch
		virtual void OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);
		virtual void OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);
		virtual void OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);
		virtual void OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);
		virtual void OnTouchMoved(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);
		virtual void OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);
		virtual void OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo);

		//Hardware butons
		virtual void OnKeyLongPressed (const Control &source, KeyCode keyCode);
		virtual void OnKeyPressed (const Control &source, KeyCode keyCode);
		virtual void OnKeyReleased (const Control &source, KeyCode keyCode);
	};
};};
