/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameEngine.h"
#include "LFGameEngineHelper.h"
#include "..\Render\GL11\LFRenderGL11.h"
#include "..\Render\_Win32_\D3D9\LFRenderD3D9.h"
#include "..\Render\_Win32_\LFRenderWindowWin32.h"
#include "..\Render\_Tizen_\LFRenderWindowTizen.h"
#include "..\Input\_Win32_\LFInputSystemGlfw.h"
#include "..\Input\_TIZEN_\LFInputSystemTizen.h"
#include "..\Audio\_Win32_\LFAudioSystemAudiere.h"
#include "..\Audio\_Tizen_\LFAudioSystemTizenPlayer.h"
#include "LFSceneGraph.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\Common\LFVFSManager.h"
#include "..\Render\LFTexture.h"
#include "..\Render\LFVertexTextureData.h"
#include "..\..\Core\IO\LFLogger.h"
#include "..\Common\LFSystemInfo.h"
#include "..\Script\LFScriptSystem.h"
#include "..\Script\Engine\GameEngine\LFGameLua.h"
#include "..\Data\LFOptionsData.h"
#include "..\Data\LFGameStateData.h"
#include "..\Data\LFLevelData.h"
#include "..\GameEngine\LFScreen.h"
#include "..\GameEngine\LFLayer.h"
#include "..\Graphics\LF2D\GUI\LFSplashControl.h"

#ifdef TIZEN
#include <app_common.h>
#endif

using namespace LFEngine::Common;
using namespace LFEngine::Data;
using namespace LFCore::IO;
using namespace LFEngine::Render::GL11;
using namespace LFEngine::Render;
using namespace LFEngine::Input;
using namespace LFEngine::Audio;
using namespace LFEngine::Script;
using namespace LFEngine::Graphics;
using namespace LFEngine::Graphics::LF2D::GUI;

namespace LFEngine { namespace GameEngine
{
	LFGameEngine *LFGameEngine::instance = nullptr;
	LFGameEngineHelper helper;

	LFGameEngine::LFGameEngine() :
		PauseResumeEvent(&LFIPauseResumeEventHandler::OnPauseResumeChanged),
		optionsData(nullptr), gameStateData(nullptr), levelData(nullptr)
	{
		LFScriptSystem::CreateInstance();
		LFVFSManager::CreateInstance();

		InitSettings();

		LFLogger::Instance().WriteOutput(LFSystemInfo::EngineInfo().ToChar());
		LFLogger::Instance().WriteOutput(LFSystemInfo::RunModeInfo().ToChar());
		helper.CreateRender();
		
		helper.CreateRenderWindow();
		LFRenderWindow::Instance()->AppInitTerminateEvent += this;
		PauseResumeEvent += LFRenderWindow::Instance();

		//#ifdef WIN32
		instance = this; //instance variable is not initialized after LFNew (CreateInstance) because update while
		LFRenderWindow::Instance()->AppInit();
		//#endif
	}

	LFGameEngine::~LFGameEngine()
	{
		LFSceneGraph::ReleaseInstance();
		helper.ReleaseAudio();
		helper.ReleaseInput();
		helper.ReleaseRenderWindow();
		helper.ReleaseRender();
		LFTexture::ReleaseList();
		LFVertexTextureData::ReleaseList();
		LFVFSManager::ReleaseInstance();
		LFScriptSystem::ReleaseInstance();
	}

	void LFGameEngine::CreateInstance()
	{
		if (instance == nullptr)
		{
			LFLogger::Instance().WriteOutput("Create GameEngine");
			instance = LFNew<LFGameEngine>(AT);
		}
	}

	void LFGameEngine::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			LFLogger::Instance().WriteOutput("Release GameEngine");

			LFDelete(instance);
		}
	}

	void LFGameEngine::InitSettings()
	{
		LFString path;
		path += "";
		#ifdef TIZEN
		path += app_get_shared_resource_path(); //path += app_get_resource_path();
		#endif

		LFString configPath;
		configPath += path;
		configPath += "Config";

		if (LFScriptSystem::Instance()->LoadScript(configPath.ToChar(), true))
		{
			LFString soundFolder;
			soundFolder += path;
			soundFolder += LFScriptSystem::Instance()->GetStringGlobal("soundFolder");

			LFString imageFolder;
			imageFolder += path;
			imageFolder += LFScriptSystem::Instance()->GetStringGlobal("imageFolder");

			LFString dataFolder;
			dataFolder += path;
			dataFolder += LFScriptSystem::Instance()->GetStringGlobal("dataFolder");

			LFString levelFolder;
			levelFolder += path;
			levelFolder += LFScriptSystem::Instance()->GetStringGlobal("levelFolder");

			LFString scriptFolder;
			scriptFolder += path;
			scriptFolder += LFScriptSystem::Instance()->GetStringGlobal("scriptFolder");

			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_NO, "");
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SOUND, soundFolder.ToNewChar());
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_IMAGE, imageFolder.ToNewChar());
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_DATA, dataFolder.ToNewChar());
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_LEVEL, levelFolder.ToNewChar());
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SCRIPT, scriptFolder.ToNewChar());

			#ifdef WIN32
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_DATA_SAVE, dataFolder.ToNewChar());
			#endif

			#ifdef TIZEN
			LFVFSManager::Instance()->AddPath(LFVFSManager::CP_DATA_SAVE, app_get_data_path());
			#endif
		}
		
		if (LFScriptSystem::Instance()->LoadScript("Settings"))
		{
			char *engineName = LFScriptSystem::Instance()->GetStringGlobal("engineName");
			char *engineVersion = LFScriptSystem::Instance()->GetStringGlobal("engineVersion");
			char *gameName = LFScriptSystem::Instance()->GetStringGlobal("gameName");
			int defaultWindowWidth = (int)LFScriptSystem::Instance()->GetNumberGlobal("defaultWindowWidth");
			int defaultWindowHeight = (int)LFScriptSystem::Instance()->GetNumberGlobal("defaultWindowHeight");
			int windowWidth = (int)LFScriptSystem::Instance()->GetNumberGlobal("windowWidth");
			int windowHeight = (int)LFScriptSystem::Instance()->GetNumberGlobal("windowHeight");
			bool vsync = LFScriptSystem::Instance()->GetBooleanGlobal("vsync");
			char *render = LFScriptSystem::Instance()->GetStringGlobal("render");
			char *splashScreenTexture = LFScriptSystem::Instance()->GetStringGlobal("splashScreenTexture");
			int splashScreenSeconds = (int)LFScriptSystem::Instance()->GetNumberGlobal("splashScreenSeconds");

			LFSystemInfo::EngineName(engineName);
			LFSystemInfo::EngineVersion(engineVersion);
			LFSystemInfo::GameName(gameName);
			LFSystemInfo::DefaultWindowWidth(defaultWindowWidth);
			LFSystemInfo::DefaultWindowHeight(defaultWindowHeight);

			#ifdef WIN32
			LFSystemInfo::WindowWidth(windowWidth);
			LFSystemInfo::WindowHeight(windowHeight);
			#endif

			LFSystemInfo::Vsync(vsync);
			LFSystemInfo::Render(render);
			LFSystemInfo::SplashScreenTexture(splashScreenTexture);
			LFSystemInfo::SplashScreenSeconds(splashScreenSeconds);
		}
	}

	void LFGameEngine::LoadGameData()
	{
		optionsData = LFNew<LFOptionsData>(AT);
		optionsData->Load();

		gameStateData = LFNew<LFGameStateData>(AT);
		gameStateData->Load();

		levelData = LFNew<LFLevelData>(AT);
		levelData->Load();
	}

	void LFGameEngine::SaveGameData()
	{
		SaveOptionsData();
		LFDelete(optionsData);

		SaveGameStateData();
		LFDelete(gameStateData);

		LFDelete(levelData);
	}

	void LFGameEngine::SaveOptionsData()
	{
		if (optionsData != nullptr)
		{
			optionsData->data.isMusicOn = LFAudioSystem::Instance()->VolumeOn(CHMusic);
			optionsData->data.isSFXOn = LFAudioSystem::Instance()->VolumeOn(CHSfx);
			optionsData->data.volumeMusic = LFAudioSystem::Instance()->Volume(CHMusic);
			optionsData->data.volumeSFX = LFAudioSystem::Instance()->Volume(CHSfx);

			optionsData->Save();
		}
	}

	void LFGameEngine::SaveGameStateData()
	{
		if (gameStateData != nullptr)
			gameStateData->Save();
	}

	void LFGameEngine::AddSplashScreen()
	{
		LFScreen *splashScreen = LFNew<LFScreen>(AT, LFString(LFSplashScreenName));
		LFSplashControl *splashCtrl = LFNew<LFSplashControl>(AT);
		LFLayer *layer = LFNew<LFLayer>(AT, LFString(LFSplashLayerName));
		splashCtrl->AttachChildren(layer);
		
		layer->Add(splashCtrl);
		splashScreen->Add((LFGameComponent *)layer);
		LFSceneGraph::Instance()->Add((LFGameComponent *)splashScreen);
	}

	void LFGameEngine::RunScript()
	{
		if (LFScriptSystem::Instance()->LoadScript("Main"))
		{
			LFScriptSystem::Instance()->CallFunction(LFGameName, LFGameOnInitName);
			LFScriptSystem::Instance()->Execute();
		}
	}

	void LFGameEngine::Exit()
	{
		LFRenderWindow::Instance()->CloseWindow();
	}

	void LFGameEngine::Pause()
	{
		LFLogger::Instance().WriteOutput("GameEngine pause");

		pauseResumeEventArgs.gameEngineRunState = LFPauseResumeEventArgs::PAUSE;
		PauseResumeEvent(pauseResumeEventArgs);

		SaveOptionsData();
		SaveGameStateData();

		LFAudioSystem::Instance()->Pause();
	}

	void LFGameEngine::Resume()
	{
		LFLogger::Instance().WriteOutput("GameEngine resume");

		pauseResumeEventArgs.gameEngineRunState = LFPauseResumeEventArgs::RESUME;
		PauseResumeEvent(pauseResumeEventArgs);

		if (LFAudioSystem::Instance() != nullptr)
			LFAudioSystem::Instance()->Continue();
	}

	void LFGameEngine::OnInitTerminateChanged(const LFAppInitTerminateEventArgs &args)
	{
		if (args.applicationState == LFAppInitTerminateEventArgs::INITIALIZING)
		{
			LoadGameData();

			helper.CreateInput();

			helper.CreateAudio();
			LFAudioSystem::Instance()->VolumeOn(CHMusic, optionsData->data.isMusicOn);
			LFAudioSystem::Instance()->VolumeOn(CHSfx, optionsData->data.isSFXOn);
			LFAudioSystem::Instance()->Volume(CHMusic, optionsData->data.volumeMusic);
			LFAudioSystem::Instance()->Volume(CHSfx, optionsData->data.volumeSFX);

			LFSceneGraph::CreateInstance();
			LFRenderWindow::Instance()->InitSceneGraph();

			RunScript();
			AddSplashScreen();
		}

		if (args.applicationState == LFAppInitTerminateEventArgs::TERMINATE)
		{
			LFScriptSystem::Instance()->CallFunction(LFGameName, LFGameOnTerminateName);
			
			PauseResumeEvent -= LFRenderWindow::Instance();
			LFRenderWindow::Instance()->AppInitTerminateEvent -= this;

			SaveGameData();
		}
	}
}}
