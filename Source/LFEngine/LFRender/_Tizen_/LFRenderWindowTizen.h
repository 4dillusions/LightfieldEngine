/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#pragma once

#include "..\LFRenderWindow.h"

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#include <tizen.h>
#include <Elementary_GL_Helpers.h>
#include <device/power.h>

typedef struct appdata
{
	//basic UI
	Evas_Object *win;

	//Conformant object for the indicator
	Evas_Object *conform;

	//OpenGL
	Evas_Object *glview;
	Ecore_Animator *anim;

} appdata_s;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	/**
		@brief
		Render window for rendering OpenGL on Tizen
	*/
	class LFRenderWindowTizen final : public LFRenderWindow
	{
		static appdata_s *ad;
		static LFRenderWindowTizen *renderWindowTizen;

	public:
		appdata_s *GetAd();

		LFRenderWindowTizen(const LFRenderWindowTizen &) = delete;
		LFRenderWindowTizen(LFRenderWindowTizen &&) = delete;
		LFRenderWindowTizen &operator=(const LFRenderWindowTizen &) = delete;
		LFRenderWindowTizen &operator=(LFRenderWindowTizen &&) = delete;

		LFRenderWindowTizen();
		~LFRenderWindowTizen() = default;

		//LFRenderWindow functions
		void InitWindow() override;
		void Update() override;
		void Foreground() override;
		void Background() override;
		void AppInit() override;
		void AppTerminate() override;
		void CloseWindow() override;

		void OnAppPauseResume(const LFGameEngine::AppPauseResumeEventArgs &appPauseResumeEventArgs) override;

		//Tizen functions
		static void WinDeleteRequestCb(void *data, Evas_Object *obj, void *event_info);
		static void CreateBaseGui(appdata_s *ad);
		static Eina_Bool AnimCb(void *data);
		static void DestroyAnim(void *data, Evas *evas, Evas_Object *obj, void *event_info);
		static void InitGl(Evas_Object *glview);
		static void DelGl(Evas_Object *glview);
		static void DrawGl(Evas_Object *glview);
		static void ResizeGl(Evas_Object *glview);
		static Evas_Object *GlviewCreate(appdata_s *ad);
		static bool AppCreate(void *data);
		static void AppControl(app_control_h app_control, void *data);
		static void AppPause(void *data);
		static void AppResume(void *data);
		static void AppTerminate(void *data);
		static void UiAppLangChanged(app_event_info_h event_info, void *user_data);
		static void UiAppOrientChanged(app_event_info_h event_info, void *user_data);
		static void UiAppRegionChanged(app_event_info_h event_info, void *user_data);
		static void UiAppLowBattery(app_event_info_h event_info, void *user_data);
		static void UiAppLowMemory(app_event_info_h event_info, void *user_data);
	};
}}}

#endif
