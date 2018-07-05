/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "LFRenderWindowTizen.h"
#include "..\LFRenderWindow.h"
#include "..\LFRender.h"
#include "..\..\Common\LFSystemInfo.h"
#include "..\..\LFCore\src\Common\LFMemoryManager.h"
#include "..\..\GameEngine\LFSceneGraph.h"
#include "..\..\GameEngine\LFGameEngine.h"
#include "..\..\Input\_Tizen_\LFInputSystemTizen.h"
#include "..\..\Soil\src\SOIL.h"

#include <app.h>
#include <tizen.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <Elementary_GL_Helpers.h>
#include <Elementary.h>
#include <dlog.h>
#include <device/power.h>
#include <Elementary.h>

using namespace LFCore::Common;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Common;

MainData MainDataHelper::mainData;

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

LFEngine::Render::LFRenderWindowTizen *renderWindowTizen;
LFEngine::Render::LFRender *render;
Evas_Object *glview;

void win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	renderWindowTizen->CloseWindow(); //ui_app_exit();
}

void create_base_gui(appdata_s *ad)
{
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win))
	{
		int rots[1] = { 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 1);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	evas_object_show(ad->win);
}

Eina_Bool _anim_cb(void *data)
{
   static appdata_s *ad = 0;
   ad = (appdata_s *)data;

   elm_glview_changed_set(ad->glview);

   return ECORE_CALLBACK_RENEW;
}

void _destroy_anim(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
   Ecore_Animator *ani = (Ecore_Animator *)data;
   ecore_animator_del(ani);
}

void init_gl(Evas_Object *glview)
{
	render->Init();
	renderWindowTizen->LFEngine::Render::LFRenderWindow::AppInit();
}

void del_gl(Evas_Object *glview)
{ }

void draw_gl(Evas_Object *glview)
{
	renderWindowTizen->Update();
}

void resize_gl(Evas_Object *glview)
{
	renderWindowTizen->Foreground();
}

Evas_Object *glview_create(appdata_s *ad)
{
   glview = elm_glview_version_add(ad->win, EVAS_GL_GLES_1_X);
   //elm_win_resize_object_add(ad->win, glview);

   elm_glview_mode_set(glview, (Elm_GLView_Mode)(ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH | ELM_GLVIEW_STENCIL));

   elm_glview_resize_policy_set(glview, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
   elm_glview_render_policy_set(glview, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);

   elm_glview_init_func_set(glview, init_gl);
   elm_glview_del_func_set(glview, del_gl);
   elm_glview_render_func_set(glview, draw_gl);
   elm_glview_resize_func_set(glview, resize_gl);

   //evas_object_size_hint_min_set(glview, 250, 250);
   evas_object_show(glview);

   return glview;
}

bool app_create(void *data)
{
	appdata_s *ad = (appdata_s *)data;

	elm_config_accel_preference_set("opengl");

	create_base_gui(ad);

	elm_win_conformant_set(ad->win, EINA_TRUE);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);

	ad->conform = elm_conformant_add(ad->win);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_size_hint_align_set(ad->conform, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(ad->conform);

	ad->glview = glview_create(ad);
	glview = ad->glview;

	elm_object_content_set(ad->conform, glview);

	SOIL_SetTizenGlView(ad->glview);

	ad->anim = ecore_animator_add(_anim_cb, ad);
	evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_DEL, _destroy_anim, ad->anim);

	evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_MOUSE_DOWN, mouse_down_cb, ad);
	evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_MOUSE_UP, mouse_up_cb, ad);
	evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_MOUSE_MOVE, mouse_move_cb, ad);

	return true;
}

void app_control(app_control_h app_control, void *data)
{ }

void app_pause(void *data)
{
	device_power_release_lock (POWER_LOCK_DISPLAY);
	renderWindowTizen->Background();
}

void app_resume(void *data)
{
	device_power_request_lock(POWER_LOCK_DISPLAY, 0);
	renderWindowTizen->Foreground();
}

void app_terminate(void *data)
{
	device_power_release_lock (POWER_LOCK_DISPLAY);
	renderWindowTizen->AppTerminate();
}

void ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);

	return;
}

void ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	return;
}

void ui_app_region_changed(app_event_info_h event_info, void *user_data)
{ }

void ui_app_low_battery(app_event_info_h event_info, void *user_data)
{ }

void ui_app_low_memory(app_event_info_h event_info, void *user_data)
{ }

namespace LFEngine { namespace Render
{
	LFRenderWindowTizen::LFRenderWindowTizen()
	{
		::renderWindowTizen = this;
		::render = this->render;
	}

	LFRenderWindowTizen::~LFRenderWindowTizen()
	{ }

	void LFRenderWindowTizen::CreateInstance()
	{
		if (instance == nullptr)
			instance = new LFRenderWindowTizen(); //Tizen app holds this: bug #3 //instance = LFNew<LFRenderWindowTizen>(AT);
	}

	void LFRenderWindowTizen::ReleaseInstance()
	{
		//Tizen app holds this: bug #3
		/*if (instance != nullptr)
			LFDelete(instance);*/
	}

	Evas_Object *LFRenderWindowTizen::GlView()
	{
		return glview;
	}
		
	void LFRenderWindowTizen::InitWindow()
	{ }

	void LFRenderWindowTizen::Update()
	{
		if (isRendering == true && isPaused == false)
		{
			::render->BeginScene();
			sceneGraph->Update(deltaTimer.DeltaTime());
			::render->EndScene();
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
		//LFRenderWindow::AppInit();

		appdata_s ad = {0,};

		ui_app_lifecycle_callback_s event_callback = {0,};
		app_event_handler_h handlers[5] = {NULL, };

		event_callback.create = app_create;
		event_callback.terminate = app_terminate;
		event_callback.pause = app_pause;
		event_callback.resume = app_resume;
		event_callback.app_control = app_control;

		ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
		ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);
		ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

		MainDataHelper::mainData.returnValue = ui_app_main(MainDataHelper::mainData.argc, MainDataHelper::mainData.argv, &event_callback, &ad);
		if (MainDataHelper::mainData.returnValue != APP_ERROR_NONE)
			dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", MainDataHelper::mainData.returnValue);
	}

	void LFRenderWindowTizen::AppTerminate()
	{
		/*glPlayer->Stop();

		if(glRenderer != nullptr)
			LFDelete(glRenderer);

		LFDelete(glPlayer);*/

		LFRenderWindow::AppTerminate();
	}

	void LFRenderWindowTizen::CloseWindow()
	{
		ui_app_exit();
	}

	void LFRenderWindowTizen::OnPauseResumeChanged(const LFPauseResumeEventArgs &args)
	{
		if (args.gameEngineRunState == LFPauseResumeEventArgs::RESUME)
			isPaused = false;

		if (args.gameEngineRunState == LFPauseResumeEventArgs::PAUSE)
			isPaused = true;
	}
}}

#endif
