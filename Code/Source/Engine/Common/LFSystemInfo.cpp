/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSystemInfo.h"
#include "..\..\Core\Common\LFDateTime.h"
#include "..\..\Core\Math\LFMath.h"
#include <ctime>

using namespace LFCore::Math;
using namespace LFCore::Common;

#ifdef TIZEN
#include <system_settings.h>
#include <system_info.h>
#endif

#ifdef WIN32
#include <Windows.h>
#endif

namespace LFEngine { namespace Common
{
	char *LFSystemInfo::engineName;
	char *LFSystemInfo::engineVersion;
	char *LFSystemInfo::gameName;
	int LFSystemInfo::windowWidth;
	int LFSystemInfo::windowHeight;
	int LFSystemInfo::defaultWindowWidth;
	int LFSystemInfo::defaultWindowHeight;
	float LFSystemInfo::windowWidthRelativeScale = 0;
	float LFSystemInfo::windowHeightRelativeScale = 0;
	bool LFSystemInfo::vsync = true;
	char *LFSystemInfo::render;
	char *LFSystemInfo::splashScreenTexture;
	int LFSystemInfo::splashScreenSeconds = 0;

	LFString LFSystemInfo::EngineInfo()
	{
		LFString result;	

		result += LFSystemInfo::EngineName();
		result += (" ");
		result += LFSystemInfo::EngineVersion();

		return result;
	}

	LFString LFSystemInfo::RunModeInfo()
	{
		LFString result;

		result += "Running mode ";

		#ifdef DEBUG
		result += "[DEBUG]";
		#else
		result += "[RELEASE]";
		#endif

		return result;
	}

	int LFSystemInfo::WindowWidth()
	{
		#ifdef TIZEN
		windowWidth = ScreenWidth();
		#endif

		return windowWidth;
	}

	int LFSystemInfo::WindowHeight()
	{
		#ifdef TIZEN
		windowHeight = ScreenHeight();
		#endif

		return windowHeight;
	}

	int LFSystemInfo::ScreenWidth()
	{
		#ifdef TIZEN
		int result = 0;
		system_info_get_platform_int("tizen.org/feature/screen.height", &result);

		return result;
		#endif

		#ifdef WIN32
		return GetSystemMetrics(SM_CXSCREEN);
		#endif
	}

	int LFSystemInfo::ScreenHeight()
	{
		#ifdef TIZEN
		int result = 0;
		system_info_get_platform_int("tizen.org/feature/screen.width", &result);

		return result;
		#endif

		#ifdef WIN32
		return GetSystemMetrics(SM_CYSCREEN);
		#endif
	}

	float LFSystemInfo::WindowWidthRelativeScale()
	{
		if (windowWidthRelativeScale == 0)
			LFSystemInfo::windowWidthRelativeScale = LFSystemInfo::WindowWidth() / (float)LFSystemInfo::DefaultWindowWidth();

		return windowWidthRelativeScale;
	}

	float LFSystemInfo::WindowHeightRelativeScale()
	{
		if (windowHeightRelativeScale == 0)
			LFSystemInfo::windowHeightRelativeScale = LFSystemInfo::WindowHeight() / (float)LFSystemInfo::DefaultWindowHeight();

		return windowHeightRelativeScale;
	}

	bool LFSystemInfo::IsSilentMode()
	{
		bool result;

		#ifdef TIZEN
		system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE, &result);
		#endif

		#ifdef WIN32
		return false;
		#endif

		return result;
	}
}}
