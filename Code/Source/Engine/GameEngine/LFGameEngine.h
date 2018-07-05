/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFEventArgs.h"

namespace LFEngine { namespace Data {
	class LFOptionsData;
	class LFGameStateData;
	class LFLevelData;
}}

namespace LFEngine { namespace GameEngine
{
	class LFENGINE_LIBRARY LFAppInitTerminateEventArgs
	{
	public:
		enum ApplicationState { INITIALIZING, TERMINATE };
		ApplicationState applicationState;
	};

	class LFENGINE_LIBRARY LFIAppInitTerminateEventHandler
	{
	public:
		virtual void OnInitTerminateChanged(const LFAppInitTerminateEventArgs &args) = 0;
		virtual ~LFIAppInitTerminateEventHandler() { }
	};

	class LFENGINE_LIBRARY LFPauseResumeEventArgs
	{
	public:
		enum GameEngineRunState { PAUSE, RESUME };
		GameEngineRunState gameEngineRunState;
	};

	class LFENGINE_LIBRARY LFIPauseResumeEventHandler
	{
	public:
		virtual void OnPauseResumeChanged(const LFPauseResumeEventArgs &args) = 0;
		virtual ~LFIPauseResumeEventHandler() { }
	};

	class LFENGINE_LIBRARY LFGameEngine : 
		public LFIAppInitTerminateEventHandler
	{
	 private:
		static LFGameEngine *instance;
		LFEngine::Data::LFOptionsData *optionsData;
		LFEngine::Data::LFGameStateData *gameStateData;
		LFEngine::Data::LFLevelData *levelData;
		LFPauseResumeEventArgs pauseResumeEventArgs;

	public:
		LFGameEngine();
		virtual ~LFGameEngine();

		static LFGameEngine *Instance() { return instance; }
		static void CreateInstance();
		static void ReleaseInstance();

		LFCore::Common::LFEventArgs<LFIPauseResumeEventHandler, LFPauseResumeEventArgs> PauseResumeEvent;

		LFEngine::Data::LFOptionsData *OptionsData() { return optionsData; }
		LFEngine::Data::LFGameStateData *GameStateData() { return gameStateData; }
		LFEngine::Data::LFLevelData *LevelData() { return levelData; }

		void InitSettings();
		void LoadGameData(); //new all data, options, game state, levels
		void SaveGameData(); //options, game state and release all data
		void SaveOptionsData();
		void SaveGameStateData();
		void AddSplashScreen();
		void RunScript();
		void Exit();
		void Pause();
		void Resume();

		virtual void OnInitTerminateChanged(const LFAppInitTerminateEventArgs &args);
	};
}}
