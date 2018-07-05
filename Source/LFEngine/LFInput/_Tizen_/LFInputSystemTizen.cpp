/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "LFInputSystemTizen.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\LFRender\_Tizen_\LFRenderWindowTizen.h"
#include "..\..\LFGameEngine\LFIGame.h"

using namespace LF3Engine::LFEngine::LFGameEngine;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFRender;
using namespace LF3Engine::LFEngine::LFInput;

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
	LFInputSystemTizen::LFInputSystemTizen()
	{
		input = this;
		game = LF3GameEngine::Instance()->GetGame();

		if (auto renderWindow = dynamic_cast<LFRenderWindowTizen *>(LFIoc<LFRenderWindow *>::Get()))
		{
			auto ad = renderWindow->GetAd();

			eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, WinBackCb, ad);
			evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_MOUSE_UP, MouseUpCb, ad);
			evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_MOUSE_DOWN, MouseDownCb, ad);
			evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_MOUSE_MOVE, MouseMoveCb, ad);
		}
	}

	void LFInputSystemTizen::WinBackCb(void *data, Evas_Object *obj, void *event_info)
	{
		hardwareButtonEventArgs.button = LFHardwareButtonTypes::Back;
		hardwareButtonEventArgs.isPressed = false;

		game->OnButtonPressRelease(hardwareButtonEventArgs);
		input->OnHardwareButtonPressRelease(hardwareButtonEventArgs);
	}

	void LFInputSystemTizen::MouseDownCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
	{
		static Evas_Event_Mouse_Up *upInfo = 0;
		upInfo = (Evas_Event_Mouse_Up *)event_info;

		if (upInfo->button == 1) //left button
		{
			pointerPressReleaseEventArgs.x = upInfo->output.x;
			pointerPressReleaseEventArgs.y = upInfo->output.y;
			pointerPressReleaseEventArgs.isPressed = true;

			game->OnPointerPressRelease(pointerPressReleaseEventArgs);
			input->OnPointerPressRelease(pointerPressReleaseEventArgs);
		}
	}

	void LFInputSystemTizen::MouseUpCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
	{
		static Evas_Event_Mouse_Up *upInfo = 0;
		upInfo = (Evas_Event_Mouse_Up *)event_info;

		if (upInfo->button == 1) //left button
		{
			pointerPressReleaseEventArgs.x = upInfo->output.x;
			pointerPressReleaseEventArgs.y = upInfo->output.y;
			pointerPressReleaseEventArgs.isPressed = false;

			game->OnPointerPressRelease(pointerPressReleaseEventArgs);
			input->OnPointerPressRelease(pointerPressReleaseEventArgs);
		}
	}

	void LFInputSystemTizen::MouseMoveCb(void *data, Evas *e, Evas_Object *obj, void *event_info)
	{
		static Evas_Event_Mouse_Move *moveInfo = 0;

		if (pointerPressReleaseEventArgs.isPressed)
		{
			moveInfo = (Evas_Event_Mouse_Move *)event_info;

			pointerMoveEventArgs.x = moveInfo->cur.output.x;
			pointerMoveEventArgs.y = moveInfo->cur.output.y;

			game->OnPointerMove(pointerMoveEventArgs);
			input->OnPointerMove(pointerMoveEventArgs);
		}
	}
}}}

#endif
