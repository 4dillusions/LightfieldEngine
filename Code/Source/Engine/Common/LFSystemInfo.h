/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFString.h"

namespace LFEngine { namespace Common
{
	class LFENGINE_LIBRARY LFSystemInfo
	{
	private:
		static char *engineName;
		static char *engineVersion;
		static char *gameName;
		static int windowWidth;
		static int windowHeight;
		static int defaultWindowWidth;
		static int defaultWindowHeight;
		static float windowWidthRelativeScale; //relative width scale from defaultWindowWidth and windowWidth
		static float windowHeightRelativeScale; //relative height scale from defaultWindowHeight and windowHeight
		static bool vsync;
		static char *render;
		static char *splashScreenTexture;
		static int splashScreenSeconds;

	public:
		LFSystemInfo();

		static char *EngineName() { return engineName; }
		static void EngineName(char *engineName) { LFSystemInfo::engineName = engineName; }
		static char *EngineVersion() { return engineVersion; }
		static void EngineVersion(char *engineVersion) { LFSystemInfo::engineVersion = engineVersion; }
		static LFCore::Common::LFString GameName() { return LFCore::Common::LFString(gameName); }
		static void GameName(char *gameName) { LFSystemInfo::gameName = gameName; }
		static LFCore::Common::LFString EngineInfo();
		static LFCore::Common::LFString RunModeInfo();
		static int WindowWidth();
		static void WindowWidth(int windowWidth) { LFSystemInfo::windowWidth = windowWidth; }
		static int WindowHeight();
		static void WindowHeight(int windowHeight) { LFSystemInfo::windowHeight = windowHeight; }
		static int DefaultWindowWidth() { return defaultWindowWidth; }
		static void DefaultWindowWidth(int defaultWindowWidth) { LFSystemInfo::defaultWindowWidth = defaultWindowWidth; }
		static int DefaultWindowHeight() { return defaultWindowHeight; }
		static void DefaultWindowHeight(int defaultWindowHeight) { LFSystemInfo::defaultWindowHeight = defaultWindowHeight; }
		static float WindowWidthRelativeScale();
		static float WindowHeightRelativeScale();
		static bool Vsync() { return vsync; }
		static void Vsync(bool vsync) { LFSystemInfo::vsync = vsync; }
		static char *Render() { return render; }
		static void Render(char *render) {  LFSystemInfo::render = render; }
		static char *SplashScreenTexture() { return splashScreenTexture; }
		static void SplashScreenTexture(char *splashScreenTexture) { LFSystemInfo::splashScreenTexture = splashScreenTexture; }
		static int SplashScreenSeconds() { return splashScreenSeconds; }
		static void SplashScreenSeconds(int splashScreenSeconds) { LFSystemInfo::splashScreenSeconds = splashScreenSeconds; }
		static int ScreenWidth();
		static int ScreenHeight();
		static bool IsSilentMode();
	};
}}
