/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFEventArgs.h"

namespace LFEngine { namespace Input
{
	#define TCLeft "TC_LEFT"
	#define TCRight "TC_RIGHT"
	
	#define BTSoundUp "BT_SOUND_UP"
	#define BTSoundDown "BT_SOUND_DOWN"
	#define BTBack "BT_BACK"

	class LFENGINE_LIBRARY LFPointerEventArgs
	{
	public:
		bool isPressed;
		int x, y;

		enum LFTouch
		{
			TC_LEFT,
			TC_RIGHT,
		};

		LFTouch touch;
	};

	class LFENGINE_LIBRARY LFPointerMoveEventArgs
	{
	public:
		int x, y;
	};

	class LFENGINE_LIBRARY LFIPointerPressReleaseEventHandler
	{
	public:
		virtual void OnPointerPressRelease(const LFPointerEventArgs &args) = 0;
		virtual ~LFIPointerPressReleaseEventHandler() { };
	};

	class LFENGINE_LIBRARY LFIPointerMoveEventHandler
	{
	public:
		virtual void OnPointerMove(const LFPointerMoveEventArgs &args) = 0;
		virtual ~LFIPointerMoveEventHandler() { };
	};

	class LFENGINE_LIBRARY LFButtonEventArgs
	{
	public:
		enum LFButton
		{
			BT_SOUND_UP,
			BT_SOUND_DOWN,
			BT_BACK,
		};

		LFButton button;
	};

	class LFENGINE_LIBRARY LFInputSystem
	{ 
	protected:
		static LFInputSystem *instance;

	public:
		LFInputSystem();
		virtual ~LFInputSystem();

		static LFInputSystem *Instance() { return instance; }

		LFCore::Common::LFEventArgs<LFIPointerPressReleaseEventHandler, LFPointerEventArgs> PointerPressReleaseEvent;
		LFCore::Common::LFEventArgs<LFIPointerMoveEventHandler, LFPointerMoveEventArgs> PointerMoveEvent;
	};
}}
