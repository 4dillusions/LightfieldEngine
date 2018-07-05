/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#pragma once

#include "..\LFRenderWindow.h"
#include <Elementary.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "lightfield2"

#if !defined(PACKAGE)
#define PACKAGE "com.4dillusions.lightfield2"
#endif

struct MainData
{
	int argc, returnValue;
	char **argv;
};

class MainDataHelper
{
private:
	MainDataHelper() { }

public:
	static MainData mainData;
};

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFRenderWindowTizen : public LFRenderWindow
	{
	public:
		LFRenderWindowTizen();
		virtual ~LFRenderWindowTizen();

		static void CreateInstance();
		static void ReleaseInstance();
		
		Evas_Object *GlView();

		virtual void InitWindow();
		virtual void Update();
		virtual void Foreground();
		virtual void Background();
		virtual void AppInit();
		virtual void AppTerminate();
		virtual void CloseWindow();
		virtual void OnPauseResumeChanged(const GameEngine::LFPauseResumeEventArgs &args);
	};
}}

#endif
