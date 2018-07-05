/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSystemData.h"
#include "LFDateTime.h"
#include "..\LFMath\LFVector2D.h"
#include "..\LFMath\LFVector4D.h"
#include "..\..\LFData\LFAppData.h"

#ifdef WIN32
	#include <Windows.h>
#endif

#ifdef TIZEN
	#include <system_settings.h>
	#include <system_info.h>
#endif

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	const char *LFSystemData::LFDataExtension = ".dat";
	
	const char *LFSystemData::LFSplashScreenName = "SplashScreen";
	const char *LFSystemData::LFMenuScreenName = "MenuScreen";
	const char *LFSystemData::LFPlayerNameScreenName = "PlayerNameScreen";
	const char *LFSystemData::LFGameScreenName = "GameScreen";
	const char *LFSystemData::LFVictoryScreenName = "VictoryScreen";

	const char *LFSystemData::LFBackLayerName = "BackgroundLayer";
	const char *LFSystemData::LFGameLayerName = "GameLayer";
	const char *LFSystemData::LFGUILayerName = "GUILayer";
	const char *LFSystemData::LFGUITextLayerName = "GUITextLayer";
	const char *LFSystemData::LFGUIMessageBackLayerName = "GUIMsgBackLayer";
	const char *LFSystemData::LFGUIMessageLayerName = "GUIMsgLayer";

	const char *LFSystemData::LFShaderEffectBasicD3D9Name = "BasicShaderD3D9";
	const char *LFSystemData::LFShaderEffectNormalD3D9Name = "NormalShaderD3D9";
	const char *LFSystemData::LFShaderEffectBasicGLES20Name = "BasicShaderGLES20";
	const char *LFSystemData::LFShaderEffectNormalGLES20Name = "NormalShaderGLES20";

	const char *LFSystemData::LFEngineName = "Lightfield engine";
	const char *LFSystemData::LFEngineVersion = "3.0";
	const int LFSystemData::LFDefaultWindowWidth = 480;
	const int LFSystemData::LFDefaultWindowHeight = 800;
	const bool LFSystemData::LFIsVsync = true;
	const char *LFSystemData::LFRender = "OpenGL20"; //"OpenGL20" "Direct3D9"
	const char *LFSystemData::LFSplashScreenTextureName = "splashBackground.jpg";
	const int LFSystemData::LFSplashScreenWaitSeconds = 2; //5

	int LFSystemData::maxTextureSize = 0;
	char *LFSystemData::gpuVendor = nullptr;
	char *LFSystemData::gpuRenderer = nullptr;
	int LFSystemData::windowWidth = 432;//480
	int LFSystemData::windowHeight = 720;//800
	float LFSystemData::windowWidthRelativeScale = 0;
	float LFSystemData::windowHeightRelativeScale = 0;

	char *const LFSystemData::LFOptionsDataName = "OptionsData.dat";
	char *const LFSystemData::LFLevelDataName = "LevelData.dat";
	char *const LFSystemData::LFGameStateDataName = "GameStateData.dat";

	char *const LFSystemData::LFAtlasName = "atlas.png";
	char *const LFSystemData::LFAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.:!? ";

	const LFVector2D LFSystemData::ButtonLeft(10, 2);
	const LFVector2D LFSystemData::ButtonCenter(11, 2);
	const LFVector2D LFSystemData::ButtonRight(12, 2);
	const LFVector2D LFSystemData::CheckMusicOn(13, 2);
	const LFVector2D LFSystemData::CheckMusicOff(14, 2);
	const LFVector2D LFSystemData::CheckSFXOn(15, 2);
	const LFVector2D LFSystemData::CheckSFXOff(0, 3);
	const LFVector2D LFSystemData::ButtonBack(1, 3);
	const LFVector2D LFSystemData::ButtonBackspace(2, 3);
	const LFVector2D LFSystemData::CheckRefresh(1, 4);
    
	LFAppData data;
	LFAppData &LFSystemData::appData = data;

	const LFAppData &LFSystemData::GetAppData()
	{
		return appData;
	}

	void LFSystemData::SetAppData(const LFAppData &appData)
	{
		LFSystemData::appData = appData;
	}

	const char *LFSystemData::GetPlatformName()
	{
		#ifdef WINCLASSIC
			return "Win32";
		#endif

		#ifdef TIZEN
			return "Tizen";
		#endif
	}

	const char *LFSystemData::GetRunMode()
	{
		#if defined(DEBUG) || defined(_DEBUG)
			return "debug";
		#else
			return "release";
		#endif
	}

	int LFSystemData::GetWindowWidth()
	{
		#ifdef TIZEN
		windowWidth = GetScreenWidth();
		#endif

		return windowWidth;
	}

	int LFSystemData::GetWindowHeight()
	{
		#ifdef TIZEN
		windowHeight = GetScreenHeight();
		#endif

		return windowHeight;
	}

	int LFSystemData::GetScreenWidth()
	{
		#ifdef WIN32
			return GetSystemMetrics(SM_CXSCREEN);
		#endif

		#ifdef TIZEN
			int result = 0;

			if (GetIsWindowOrientationPortrait())
				system_info_get_platform_int("tizen.org/feature/screen.width", &result);
			else
				system_info_get_platform_int("tizen.org/feature/screen.height", &result);

			return result;
		#endif
	}

	int LFSystemData::GetScreenHeight()
	{
		#ifdef WIN32
			return GetSystemMetrics(SM_CYSCREEN);
		#endif

		#ifdef TIZEN
			int result = 0;

			if (GetIsWindowOrientationPortrait())
				system_info_get_platform_int("tizen.org/feature/screen.height", &result);
			else
				system_info_get_platform_int("tizen.org/feature/screen.width", &result);

			return result;
		#endif
	}

	bool LFSystemData::GetIsWindowOrientationPortrait()
	{
		return LFDefaultWindowHeight > LFDefaultWindowWidth;
	}

	float LFSystemData::GetWindowWidthRelativeScale()
	{
		if (windowWidthRelativeScale == 0)
			windowWidthRelativeScale = GetWindowWidth() / static_cast<float>(LFDefaultWindowWidth);

		return windowWidthRelativeScale;
	}

	float LFSystemData::GetWindowHeightRelativeScale()
	{
		if (windowHeightRelativeScale == 0)
			windowHeightRelativeScale = GetWindowHeight() / static_cast<float>(LFDefaultWindowHeight);

		return windowHeightRelativeScale;
	}

	bool LFSystemData::GetIsSilentMode()
	{
		#ifdef TIZEN
            bool result;
            system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_SILENT_MODE, &result);

            return result;
		#endif

		#ifdef WINCLASSIC
			return false;
		#endif
	}

	void LFSystemData::SetGPUName(char *vendor, char *renderer)
	{
		gpuVendor = vendor;
		gpuRenderer = renderer;
	}

	LFString LFSystemData::GetGPUName()
	{
		return LFString(gpuVendor) + " " + gpuRenderer;
	}

	void LFSystemData::SetMaxTextureSize(int maxTextureSize)
	{
		LFSystemData::maxTextureSize = maxTextureSize;
	}

	int LFSystemData::GetMaxTextureSize()
	{
		return maxTextureSize;
	}

	LFString LFSystemData::GetSystemInfo()
	{
		LFString result;
		LFString timeStamp = LFDateTime::GetTimeStamp();

		result += LFString("start ") + LFEngineName + " " + LFEngineVersion + '\n';
		result += timeStamp + LFString("platform: ") + GetPlatformName() + '\n';
		result += timeStamp + LFString("run mode: ") + GetRunMode() + '\n';
		result += timeStamp + LFString("renderer: ") + LFRender + '\n';
		result += timeStamp + LFString("GPU name: ") + GetGPUName() + '\n';
		result += timeStamp + LFString("maximum texture size: ") + GetMaxTextureSize() + '\n';
		result += timeStamp + LFString("screen size: ") + GetScreenWidth() + " X " + GetScreenHeight() + '\n';
		result += timeStamp + LFString("window orientation mode: ") + (GetIsWindowOrientationPortrait() ? "portrait" : "landscape") + '\n';
		result += timeStamp + LFString("window size: ") + windowWidth + " X " + windowHeight + '\n';
		result += timeStamp + LFString("vsync: ") + (LFIsVsync ? "true" : "false") + '\n';
		result += timeStamp + LFString("game name: ") + GetAppData().logTag;

		return result;
	}

	LFVector2D &LFSystemData::GetLFAlphabetCoord(char character)
	{
		static LFVector2D LFAlphabetCoords[256];

		if (LFAlphabetCoords[static_cast<int>('A')].x == 0 && LFAlphabetCoords[static_cast<int>('A')].y == 0) //didn't fill
		{
			auto SetAlphabetCoord = [](LFVector2D coord, int index)
			{
				LFAlphabetCoords[index].x = coord.x;
				LFAlphabetCoords[index].y = coord.y;
			};

			for (int i = static_cast<int>('A'), x = 0; i < static_cast<int>('P') + 1; i++, x++)
				SetAlphabetCoord(LFVector2D(x, 0), i);

			for (int i = static_cast<int>('Q'), x = 0; i < static_cast<int>('Z') + 1; i++, x++)
				SetAlphabetCoord(LFVector2D(x, 1), i);

			for (int i = static_cast<int>('1'), x = 10; i < static_cast<int>('6') + 1; i++, x++)
				SetAlphabetCoord(LFVector2D(x, 1), i);

			SetAlphabetCoord(LFVector2D(0, 2), static_cast<int>('7'));
			SetAlphabetCoord(LFVector2D(1, 2), static_cast<int>('8'));
			SetAlphabetCoord(LFVector2D(2, 2), static_cast<int>('9'));
			SetAlphabetCoord(LFVector2D(3, 2), static_cast<int>('0'));

			SetAlphabetCoord(LFVector2D(4, 2), static_cast<int>('.'));
			SetAlphabetCoord(LFVector2D(5, 2), static_cast<int>(':'));
			SetAlphabetCoord(LFVector2D(6, 2), static_cast<int>('!'));
			SetAlphabetCoord(LFVector2D(7, 2), static_cast<int>('?'));
			SetAlphabetCoord(LFVector2D(8, 2), static_cast<int>(' '));
		}

		return LFAlphabetCoords[(static_cast<int>(character))];
	}
}}}}
