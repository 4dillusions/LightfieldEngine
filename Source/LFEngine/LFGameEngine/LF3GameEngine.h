/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFEvent.h"

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	class LFOptionsData;
	class LFGameStateData;
	class LFLevelData;
	struct LevelMatrixData;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFGameEngine
{
	class LFIGame;

	struct AppInitTerminateEventArgs { enum class AppLifeState { Init, Terminate }; AppLifeState appLifeState; };
	struct AppPauseResumeEventArgs { enum class AppRunState { Pause, Resume }; AppRunState appRunState; };

	/** 
		@brief 
		GameEngine is the Facade for all (Bridges) subsystems
	*/
	class LF3GameEngine final
	{
		static LF3GameEngine *instance;

		LFIGame *game;
		
		LFData::LFOptionsData *optionsData;
		LFData::LFGameStateData *gameStateData;
		LFData::LFLevelData *levelData;
		int levelFileIndex;

		LF3GameEngine(const LF3GameEngine&) = delete;
		LF3GameEngine(LF3GameEngine &&) = delete;
		LF3GameEngine &operator=(const LF3GameEngine &) = delete;
		LF3GameEngine &operator=(LF3GameEngine &&) = delete;

	public:
		LFCore::LFCommon::LFEvent<AppPauseResumeEventArgs> OnAppPauseResume;

		LF3GameEngine(LFIGame *game);
		~LF3GameEngine();

		static LF3GameEngine *Instance() { return instance; }
		LFIGame *GetGame() const;

		static void CreateInstance(LFIGame *game);
		static void ReleaseInstance();

		LFData::LFOptionsData *GetOptionsData() const;
		LFData::LFGameStateData *GetGameStateData() const;

	private:
		LFData::LFLevelData *GetLevelData(int levelIndex); //LevelData with 100 levels. levelIndex: 0-2499, for example levelIndex = 122 => level1.dat 100-199 levels (load is cached)

	public:
		LFData::LevelMatrixData GetLevelMatrixData(int levelIndex); //LevelMatrixData with 100 levels. levelIndex: 0-2499, for example levelIndex = 122 => level1.dat 100-199 levels (load is cached)
		void LoadGameData();
		void SaveGameData();
		void SaveOptionsData() const;
		void SaveGameStateData() const;
		void AddScreens() const;
		void Pause();
		void Resume();
		static void Exit();

		void OnAppInitTerminate(const AppInitTerminateEventArgs &appInitTerminateEventArgs);
	};
}}}
