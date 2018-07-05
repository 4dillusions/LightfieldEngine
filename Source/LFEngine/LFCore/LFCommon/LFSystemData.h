/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFString.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFVector2D;
	class LFVector4D;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	struct LFAppData;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	/**
		@brief
		Config options, OS and Hardware info
	*/
	class LFSystemData final
	{
		LFSystemData() = delete;
		LFSystemData(const LFSystemData&) = delete;
		LFSystemData(LFSystemData &&) = delete;
		LFSystemData &operator=(const LFSystemData &) = delete;
		LFSystemData &operator=(LFSystemData &&) = delete;
		~LFSystemData() = delete;

	public:
        static const char *LFDataExtension;
		
		static const char *LFSplashScreenName;
		static const char *LFMenuScreenName;
		static const char *LFPlayerNameScreenName;
		static const char *LFGameScreenName;
		static const char *LFVictoryScreenName;
		
		static const char *LFBackLayerName;
		static const char *LFGameLayerName;
		static const char *LFGUILayerName;
		static const char *LFGUIMessageBackLayerName;
		static const char *LFGUITextLayerName;
		static const char *LFGUIMessageLayerName;

		static const char *LFShaderEffectBasicD3D9Name;
		static const char *LFShaderEffectNormalD3D9Name;
		static const char *LFShaderEffectBasicGLES20Name;
		static const char *LFShaderEffectNormalGLES20Name;

		static const char *LFEngineName;
		static const char *LFEngineVersion;
		static const int LFDefaultWindowWidth;
		static const int LFDefaultWindowHeight;
		static const bool LFIsVsync;
		static const char *LFRender;
		static const char *LFSplashScreenTextureName;
		static const int LFSplashScreenWaitSeconds;

		static char *const LFOptionsDataName;
		static char *const LFLevelDataName;
		static char *const LFGameStateDataName;

		static const int LFDataMaxLevelCount = 100; //how many levels are in a LevelDataFile
		static const int LFDataMaxLevelFileCount = 25; //how many level files are there
		static const int LFDataMaxLevelSize = 50;
		static const int LFDataAtlasWidth = 16; //Atlas size will be 2048x2048 with 16x16 tile matrix. (256 tiles)
		static const int LFDataAtlasHeight = 16;

		static char *const LFAtlasName;

		static char *const LFAlphabet;
		static const int LFAlphabetSize = 41;
		static LFMath::LFVector2D &GetLFAlphabetCoord(char character);

		static const LFMath::LFVector2D ButtonLeft;
		static const LFMath::LFVector2D ButtonCenter;
		static const LFMath::LFVector2D ButtonRight;
		static const LFMath::LFVector2D CheckMusicOn;
		static const LFMath::LFVector2D CheckMusicOff;
		static const LFMath::LFVector2D CheckSFXOn;
		static const LFMath::LFVector2D CheckSFXOff;
		static const LFMath::LFVector2D ButtonBack;
		static const LFMath::LFVector2D ButtonBackspace;
		static const LFMath::LFVector2D CheckRefresh;

		static const int LFOptionsDataId = 1;
		static const int LFGameStateDataId = 2;
		static const int LFLevelDataId = 3;

	private:
		static int maxTextureSize;
		static char *gpuVendor;
		static char *gpuRenderer;
		static int windowWidth;
		static int windowHeight;
		static float windowWidthRelativeScale;
		static float windowHeightRelativeScale;

		static LFData::LFAppData &appData;

	public:
		static const LFData::LFAppData &GetAppData();
		static void SetAppData(const LFData::LFAppData &appData);

		static const char *GetPlatformName();
		static const char *GetRunMode();
		static int GetWindowWidth();
		static int GetWindowHeight();
		static int GetScreenWidth();
		static int GetScreenHeight();
		static float GetWindowWidthRelativeScale();
		static float GetWindowHeightRelativeScale();
		static bool GetIsWindowOrientationPortrait();
		static bool GetIsSilentMode();
		static void SetGPUName(char *vendor, char *renderer);
		static LFString GetGPUName();
		static void SetMaxTextureSize(int maxTextureSize);
		static int GetMaxTextureSize();

		static LFString GetSystemInfo();
	};
}}}}
