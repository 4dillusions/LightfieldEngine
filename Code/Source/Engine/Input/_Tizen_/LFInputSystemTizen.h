/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#pragma once

#include "..\LFInputSystem.h"
#include <Elementary.h>

void mouse_down_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);
void mouse_up_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);
void win_back_cb(void *data, Evas_Object *obj, void *event_info); //back hardware button
void mouse_move_cb(void *data, Evas *e, Evas_Object *obj, void *event_info);

namespace LFEngine { namespace Input
{
	/*
	Hardware buttons, touch screen
	*/
	class LFENGINE_LIBRARY LFInputSystemTizen : public LFInputSystem
	{ 
	public:
		LFInputSystemTizen();
		virtual ~LFInputSystemTizen();

		static void CreateInstance();
		static void ReleaseInstance();
	};
}}

#endif
