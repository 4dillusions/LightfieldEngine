/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "LFRenderWindowTizen.h"
#include "..\LFIRenderSystem.h"
#include "..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFData\LFAppData.h"
#include "..\..\LFScene\LFSceneGraph.h"
#include "..\..\..\ThirdParty\SOIL2\SOIL2.h"
#include <efl_util.h>

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFGameEngine;
using namespace LF3Engine::LFEngine::LFData;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFRenderWindowTizen *LFRenderWindowTizen::renderWindowTizen = nullptr;
	appdata_s *LFRenderWindowTizen::ad = nullptr;

	appdata_s *LFRenderWindowTizen::GetAd()
	{
		return ad;
	}

	LFRenderWindowTizen::LFRenderWindowTizen()
	{
		renderWindowTizen = this;
	}

	void LFRenderWindowTizen::InitWindow()
	{ }

	void LFRenderWindowTizen::Update()
	{
		if (isRendering == true && isPaused == false)
		{
			render->BeginScene();
			sceneGraph->Update(deltaTimer.DeltaTime());
			render->EndScene();
		}
		else
			sleep(1);
	}

	void LFRenderWindowTizen::Foreground()
	{
		LFRenderWindow::Foreground();
	}

	void LFRenderWindowTizen::Background()
	{
		LFRenderWindow::Background();
	}

	void LFRenderWindowTizen::AppInit()
	{
		InitWindow();

		appdata_s ad = {0,};

		ui_app_lifecycle_callback_s event_callback = {0,};
		app_event_handler_h handlers[5] = {NULL, };

		event_callback.create = AppCreate;
		event_callback.terminate = AppTerminate;
		event_callback.pause = AppPause;
		event_callback.resume = AppResume;
		event_callback.app_control = AppControl;

		ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, UiAppLowBattery, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, UiAppLowMemory, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, UiAppOrientChanged, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, UiAppLangChanged, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, UiAppRegionChanged, &ad);

		auto appData = LFSystemData::GetAppData();
		appData.returnValue = ui_app_main(LFSystemData::GetAppData().argc, LFSystemData::GetAppData().argv, &event_callback, &ad);
		LFSystemData::SetAppData(appData);
		if (LFSystemData::GetAppData().returnValue != APP_ERROR_NONE)
			dlog_print(DLOG_ERROR, LFSystemData::GetAppData().logTag, "app_main() is failed. err = %d", LFSystemData::GetAppData().returnValue);
	}

	void LFRenderWindowTizen::AppTerminate()
	{
		LFRenderWindow::AppTerminate();
	}

	void LFRenderWindowTizen::CloseWindow()
	{
		ui_app_exit();
	}

	void LFRenderWindowTizen::OnAppPauseResume(const LFGameEngine::AppPauseResumeEventArgs &appPauseResumeEventArgs)
	{
        if (appPauseResumeEventArgs.appRunState == LFGameEngine::AppPauseResumeEventArgs::AppRunState::Resume)
            isPaused = false;

        if (appPauseResumeEventArgs.appRunState == LFGameEngine::AppPauseResumeEventArgs::AppRunState::Pause)
            isPaused = true;
    }

	void LFRenderWindowTizen::WinDeleteRequestCb(void *data, Evas_Object *obj, void *event_info)
	{
		renderWindowTizen->CloseWindow();
	}

	void LFRenderWindowTizen::CreateBaseGui(appdata_s *ad)
	{
		ad->win = elm_win_util_standard_add(LFSystemData::GetAppData().package, LFSystemData::GetAppData().package);
		elm_win_autodel_set(ad->win, EINA_TRUE);

		if (elm_win_wm_rotation_supported_get(ad->win))
		{
			int rots[1];
			rots[0] = LFSystemData::GetIsWindowOrientationPortrait() ? 0 : 270;
			elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 1);
		}

		evas_object_smart_callback_add(ad->win, "delete,request", WinDeleteRequestCb, NULL);
		evas_object_show(ad->win);
	}

	Eina_Bool LFRenderWindowTizen::AnimCb(void *data)
	{
		static appdata_s *ad = 0;
		ad = (appdata_s *)data;

		elm_glview_changed_set(ad->glview);

		return ECORE_CALLBACK_RENEW;
	}

	void LFRenderWindowTizen::DestroyAnim(void *data, Evas *evas, Evas_Object *obj, void *event_info)
	{
		Ecore_Animator *ani = (Ecore_Animator *)data;
		ecore_animator_del(ani);
	}

	void LFRenderWindowTizen::InitGl(Evas_Object *glview)
	{
		renderWindowTizen->render->Init();
		renderWindowTizen->LFEngine::LFRender::LFRenderWindow::AppInit();
	}

	void LFRenderWindowTizen::DelGl(Evas_Object *glview)
	{ }

	void LFRenderWindowTizen::DrawGl(Evas_Object *glview)
	{
		renderWindowTizen->Update();
	}

	void LFRenderWindowTizen::ResizeGl(Evas_Object *glview)
	{
		renderWindowTizen->Foreground();
	}

	Evas_Object *LFRenderWindowTizen::GlviewCreate(appdata_s *ad)
	{
		ad->glview = elm_glview_version_add(ad->win, EVAS_GL_GLES_2_X);

		elm_glview_mode_set(ad->glview, (Elm_GLView_Mode)(ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH | ELM_GLVIEW_STENCIL));

		elm_glview_resize_policy_set(ad->glview, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
		elm_glview_render_policy_set(ad->glview, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);

		elm_glview_init_func_set(ad->glview, InitGl);
		elm_glview_del_func_set(ad->glview, DelGl);
		elm_glview_render_func_set(ad->glview, DrawGl);
		elm_glview_resize_func_set(ad->glview, ResizeGl);

		evas_object_show(ad->glview);

		return ad->glview;
	}

	bool LFRenderWindowTizen::AppCreate(void *data)
	{
		appdata_s *ad = (appdata_s *)data;

		elm_config_accel_preference_set("opengl");

		CreateBaseGui(ad);

		elm_win_conformant_set(ad->win, EINA_TRUE);
		elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
		elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);

		ad->conform = elm_conformant_add(ad->win);
		elm_win_resize_object_add(ad->win, ad->conform);
		evas_object_size_hint_align_set(ad->conform, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_show(ad->conform);

		ad->glview = GlviewCreate(ad);
		LFRenderWindowTizen::ad = ad;

		elm_object_content_set(ad->conform, ad->glview);

		SOIL_SetTizenGlView(ad->glview);

		ad->anim = ecore_animator_add(AnimCb, ad);
		evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_DEL, DestroyAnim, ad->anim);

		return true;
	}

	void LFRenderWindowTizen::AppControl(app_control_h app_control, void *data)
	{ }

	void LFRenderWindowTizen::AppPause(void *data)
	{
		efl_util_set_window_screen_mode(LFRenderWindowTizen::ad->win, EFL_UTIL_SCREEN_MODE_DEFAULT);
		renderWindowTizen->Background();
	}

	void LFRenderWindowTizen::AppResume(void *data)
	{
		efl_util_set_window_screen_mode(LFRenderWindowTizen::ad->win, EFL_UTIL_SCREEN_MODE_ALWAYS_ON);
		renderWindowTizen->Foreground();
	}

	void LFRenderWindowTizen::AppTerminate(void *data)
	{
		efl_util_set_window_screen_mode(LFRenderWindowTizen::ad->win, EFL_UTIL_SCREEN_MODE_DEFAULT);
		renderWindowTizen->AppTerminate();
	}

	void LFRenderWindowTizen::UiAppLangChanged(app_event_info_h event_info, void *user_data)
	{
		char *locale = NULL;
		system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
		elm_language_set(locale);
		free(locale);

		return;
	}

	void LFRenderWindowTizen::UiAppOrientChanged(app_event_info_h event_info, void *user_data)
	{
		return;
	}

	void LFRenderWindowTizen::UiAppRegionChanged(app_event_info_h event_info, void *user_data)
	{ }

	void LFRenderWindowTizen::UiAppLowBattery(app_event_info_h event_info, void *user_data)
	{ }

	void LFRenderWindowTizen::UiAppLowMemory(app_event_info_h event_info, void *user_data)
	{ }
}}}

#endif
