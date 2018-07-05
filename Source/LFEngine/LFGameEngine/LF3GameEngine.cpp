/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LF3GameEngine.h"
#include "LF3GameEngineFactory.h"
#include "LFIGame.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFCommon\LFMemoryManager.h"
#include "..\LFCore\LFCommon\LFVFSManager.h"
#include "..\LFCore\LFCommon\LFSystemData.h"
#include "..\LFScene\LFSceneGraph.h"
#include "..\LFScene\LFScreen.h"
#include "..\LFScene\LFLayer.h"
#include "..\LFGUI\LFTimerControl.h"
#include "..\LFRender\LFRenderWindow.h"
#include "..\LFAudio\LFAudioSystem.h"
#include "..\LFData\LFOptionsData.h"
#include "..\LFData\LFGameStateData.h"
#include "..\LFData\LFLevelData.h"

using namespace std;
using namespace placeholders;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFScene;
using namespace LF3Engine::LFEngine::LFGUI;
using namespace LF3Engine::LFEngine::LFRender;
using namespace LF3Engine::LFEngine::LFAudio;
using namespace LF3Engine::LFEngine::LFData;

namespace LF3Engine { namespace LFEngine { namespace LFGameEngine
{
	LF3GameEngine *LF3GameEngine::instance = nullptr;

	LF3GameEngine::LF3GameEngine(LFIGame *game) : optionsData(nullptr), gameStateData(nullptr), levelData(nullptr), levelFileIndex(-1)
	{
		instance = this;
		this->game = game;

		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();

		LF3GameEngineFactory::CreateRenderComponentList();

		LF3GameEngineFactory::CreateRenderSystem();
		LF3GameEngineFactory::CreateRenderWindow();

		LFIoc<LFRenderWindow *>::Get()->OnAppInitTerminate += bind(&LF3GameEngine::OnAppInitTerminate, this, _1);
		LFIoc<LFRenderWindow *>::Get()->AppInit();
	}

	LF3GameEngine::~LF3GameEngine()
	{
		LFIoc<LFSceneGraph *>::Release();
		LF3GameEngineFactory::ReleaseAudio();
		LF3GameEngineFactory::ReleaseInput();
		LF3GameEngineFactory::ReleaseRenderWindow();
		LF3GameEngineFactory::ReleaseRenderSystem();
		LF3GameEngineFactory::ReleaseRenderComponentList();
		LFIoc<LFVFSManager *>::Release();
		LFMemoryManager::Delete(game);
	}

	LFIGame *LF3GameEngine::GetGame() const
	{
		return game;
	}

	void LF3GameEngine::CreateInstance(LFIGame *game)
	{
		if (instance == nullptr)
		{
			#ifdef WINCLASSIC
				LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToFile, true);
			#endif

			LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToOutput, true);

			LFIoc<LFLogger>::Get().WriteOutput("Create GameEngine");
			instance = LFMemoryManager::New<LF3GameEngine>(INFO, game);
		}
	}

	void LF3GameEngine::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			LFMemoryManager::Delete(instance);
			LFIoc<LFLogger>::Get().WriteOutput("Release GameEngine");
		}
	}

	LFOptionsData *LF3GameEngine::GetOptionsData() const
	{
		return optionsData;
	}

	LFGameStateData *LF3GameEngine::GetGameStateData() const
	{
		return gameStateData;
	}

	LFLevelData *LF3GameEngine::GetLevelData(int levelIndex)
	{
		if (levelIndex >= 0 && levelIndex < LFSystemData::LFDataMaxLevelCount * LFSystemData::LFDataMaxLevelFileCount)
		{
			if (levelFileIndex != levelIndex / LFSystemData::LFDataMaxLevelCount)
			{
				if (levelData != nullptr)
					LFMemoryManager::Delete(levelData);

				levelFileIndex = levelIndex / LFSystemData::LFDataMaxLevelCount;
				levelData = LFMemoryManager::New<LFLevelData>(INFO);
				levelData->Load(levelFileIndex);
			}
		}
		
		return levelData;
	}

	LevelMatrixData LF3GameEngine::GetLevelMatrixData(int levelIndex)
	{
		LevelMatrixData result;

		if (auto data = GetLevelData(levelIndex))
		{
			int level = levelIndex % LFSystemData::LFDataMaxLevelCount;

			for (int x = 0; x < LFSystemData::LFDataMaxLevelSize; x++)
				for (int y = 0; y < LFSystemData::LFDataMaxLevelSize; y++)
					result.levelMatrix[x][y] = data->data.levelMatrix[level][x][y];
		}

		return result;
	}

	void LF3GameEngine::LoadGameData()
	{
		optionsData = LFMemoryManager::New<LFOptionsData>(INFO);
		optionsData->Load();

		if (optionsData != nullptr && LFIoc<LFAudioSystem *>::IsExist())
		{
			optionsData->data.isMusicOn = LFIoc<LFAudioSystem *>::Get()->GetIsVolumeOnMusic();
			optionsData->data.isSFXOn = LFIoc<LFAudioSystem *>::Get()->GetIsVolumeOnSfx();
			optionsData->data.volumeMusic = LFIoc<LFAudioSystem *>::Get()->GetVolumeMusic();
			optionsData->data.volumeSFX = LFIoc<LFAudioSystem *>::Get()->GetVolumeSfx();
		}

		gameStateData = LFMemoryManager::New<LFGameStateData>(INFO);
		gameStateData->Load();
	}

	void LF3GameEngine::SaveGameData()
	{
		if (optionsData != nullptr)
		{
			SaveOptionsData();
			LFMemoryManager::Delete(optionsData);
		}

		if (gameStateData != nullptr)
		{
			SaveGameStateData();
			LFMemoryManager::Delete(gameStateData);
		}

		if (levelData != nullptr)
		{
			LFMemoryManager::Delete(levelData);
			levelFileIndex = -1;
		}
	}

	void LF3GameEngine::SaveOptionsData() const
	{
		if (optionsData != nullptr && LFIoc<LFAudioSystem *>::IsExist())
		{
			optionsData->data.isMusicOn = LFIoc<LFAudioSystem *>::Get()->GetIsVolumeOnMusic();
			optionsData->data.isSFXOn = LFIoc<LFAudioSystem *>::Get()->GetIsVolumeOnSfx();
			optionsData->data.volumeMusic = LFIoc<LFAudioSystem *>::Get()->GetVolumeMusic();
			optionsData->data.volumeSFX = LFIoc<LFAudioSystem *>::Get()->GetVolumeSfx();

			optionsData->Save();
		}
	}

	void LF3GameEngine::SaveGameStateData() const
	{
		if (gameStateData != nullptr)
			gameStateData->Save();
	}

	void LF3GameEngine::AddScreens() const
	{
		static LFScreen *splashScreen = LFMemoryManager::New<LFScreen>(INFO, LFString(LFSystemData::LFSplashScreenName)); //static for local lambda expression
		splashScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFBackLayerName)));
		splashScreen->AddBackground(LFString("BackgroundImage"), LFString(LFSystemData::LFSplashScreenTextureName)); //loading...
		LFTimerControl *timer = LFMemoryManager::New<LFTimerControl>(INFO, LFString("SplashTimer"), 1);
		splashScreen->AddGUIObject(LFString(LFSystemData::LFBackLayerName), timer);
		LFIoc<LFSceneGraph *>::Get()->Add(splashScreen);
		LFIoc<LFSceneGraph *>::Get()->SetActiveScreen(splashScreen);

		LFScreen *menuScreen = LFMemoryManager::New<LFScreen>(INFO, LFString(LFSystemData::LFMenuScreenName));
		menuScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFBackLayerName)));
		menuScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUILayerName)));
		LFIoc<LFSceneGraph *>::Get()->Add(menuScreen);
			
		LFScreen *gameScreen = LFMemoryManager::New<LFScreen>(INFO, LFString(LFSystemData::LFGameScreenName));
		gameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFBackLayerName)));
		gameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGameLayerName)));
		gameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUILayerName)));
		gameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUITextLayerName)));
		gameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUIMessageBackLayerName)));
		gameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUIMessageLayerName)));
		LFIoc<LFSceneGraph *>::Get()->Add(gameScreen);
		
		LFScreen *playerNameScreen = LFMemoryManager::New<LFScreen>(INFO, LFString(LFSystemData::LFPlayerNameScreenName));
		playerNameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFBackLayerName)));
		playerNameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUILayerName)));
		playerNameScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFGUIMessageLayerName)));
		LFIoc<LFSceneGraph *>::Get()->Add(playerNameScreen);

		LFScreen *victoryScreen = LFMemoryManager::New<LFScreen>(INFO, LFString(LFSystemData::LFVictoryScreenName));
		victoryScreen->Add(LFMemoryManager::New<LFLayer>(INFO, LFString(LFSystemData::LFBackLayerName)));
		LFIoc<LFSceneGraph *>::Get()->Add(victoryScreen);

		timer->Start();
		timer->TickEvent += [](const LFTimerControl &args)
		{
			static int seconds = 0;
			seconds++;
			if (seconds == 1)
			{
				LFIoc<LFLogger>::Get().WriteOutput("SplashScreenTimer first second");

				//Game side: load scene graph
				Instance()->GetGame()->OnInitGame();
			}

			if (seconds == LFSystemData::LFSplashScreenWaitSeconds)
			{
				const_cast<LFTimerControl &>(args).Stop();
				LFIoc<LFLogger>::Get().WriteOutput("SplashScreenTimer last second");

				//remove splash and its contents, activate menu screen
				splashScreen->SetIsAlive(false);

				//Game side: play menu music
				Instance()->GetGame()->OnLoadedGame();
			}
		};
	}

	void LF3GameEngine::Pause()
	{
		LFIoc<LFLogger>::Get().WriteOutput("GameEngine pause");

		OnAppPauseResume(AppPauseResumeEventArgs { AppPauseResumeEventArgs::AppRunState::Pause });

		SaveOptionsData();
		SaveGameStateData();

		LFIoc<LFAudioSystem *>::Get()->StopSfx();
		LFIoc<LFAudioSystem *>::Get()->PauseMusic();
	}

	void LF3GameEngine::Resume()
	{
		LFIoc<LFLogger>::Get().WriteOutput("GameEngine resume");

		OnAppPauseResume(AppPauseResumeEventArgs{ AppPauseResumeEventArgs::AppRunState::Resume });

		if (LFIoc<LFAudioSystem *>::IsExist())
			LFIoc<LFAudioSystem *>::Get()->ContinueMusic();
	}

	void LF3GameEngine::Exit()
	{
		LFIoc<LFRenderWindow *>::Get()->CloseWindow();
	}

	void LF3GameEngine::OnAppInitTerminate(const AppInitTerminateEventArgs &appInitTerminateEventArgs)
	{
		if (appInitTerminateEventArgs.appLifeState == AppInitTerminateEventArgs::AppLifeState::Init)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFSystemData::GetSystemInfo());

			LoadGameData();

			LF3GameEngineFactory::CreateInput();

			LF3GameEngineFactory::CreateAudio();		
			LFIoc<LFAudioSystem *>::Get()->SetIsVolumeOnMusic(optionsData->data.isMusicOn);
			LFIoc<LFAudioSystem *>::Get()->SetIsVolumeOnSfx(optionsData->data.isSFXOn);
			LFIoc<LFAudioSystem *>::Get()->SetVolumeMusic(optionsData->data.volumeMusic);
			LFIoc<LFAudioSystem *>::Get()->SetVolumeSfx(optionsData->data.volumeSFX);

			LFIoc<LFSceneGraph *>::Register<LFSceneGraph>();
			LFIoc<LFSceneGraph *>::Create();
			LFIoc<LFRenderWindow *>::Get()->InitSceneGraph();

			AddScreens();
		}

		if (appInitTerminateEventArgs.appLifeState == AppInitTerminateEventArgs::AppLifeState::Terminate)
		{
			game->OnTerminateGame();
			LFIoc<LFRenderWindow *>::Get()->OnAppInitTerminate -= bind(&LF3GameEngine::OnAppInitTerminate, this, _1);

			SaveGameData();
		}
	}
}}}
