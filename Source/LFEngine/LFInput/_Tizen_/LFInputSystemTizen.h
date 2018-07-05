/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#pragma once

#include "..\LFInputSystem.h"
#include <Elementary.h>

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
    class LFInputSystemTizen final : public LFInputSystem
	{
    	LFInputSystemTizen(const LFInputSystemTizen &) = delete;
    	LFInputSystemTizen(LFInputSystemTizen &&) = delete;
    	LFInputSystemTizen &operator=(const LFInputSystemTizen &) = delete;
    	LFInputSystemTizen &operator=(LFInputSystemTizen &&) = delete;

	public:
    	LFInputSystemTizen();
        ~LFInputSystemTizen() = default;

        //Tizen functions
        static void WinBackCb(void *data, Evas_Object *obj, void *event_info); //back hardware button
        static void MouseDownCb(void *data, Evas *e, Evas_Object *obj, void *event_info);
        static void MouseUpCb(void *data, Evas *e, Evas_Object *obj, void *event_info);
        static void MouseMoveCb(void *data, Evas *e, Evas_Object *obj, void *event_info);
	};
}}}

#endif
