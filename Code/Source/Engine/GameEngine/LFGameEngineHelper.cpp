/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameEngineHelper.h"
#include "..\Render\GL11\LFRenderGL11.h"
#include "..\Render\_Win32_\D3D9\LFRenderD3D9.h"
#include "..\Render\_Win32_\LFRenderWindowWin32.h"
#include "..\Render\_Tizen_\LFRenderWindowTizen.h"
#include "..\Input\_Win32_\LFInputSystemGlfw.h"
#include "..\Input\_TIZEN_\LFInputSystemTizen.h"
#include "..\Audio\_Win32_\LFAudioSystemAudiere.h"
#include "..\Audio\_Tizen_\LFAudioSystemTizenPlayer.h"
#include "..\..\Core\\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFEngine::Render;
using namespace LFEngine::Input;
using namespace LFEngine::Audio;

namespace LFEngine { namespace GameEngine
{
	void LFGameEngineHelper::CreateRender()
	{
		switch(LFRender::RenderType())
		{
			case LFRender::RT_OpenGL11: LFEngine::Render::GL11::LFRenderGL11::CreateInstance(); break;

			case LFRender::RT_Direct3D9:
				#ifdef WIN32
				LFEngine::Render::D3D9::LFRenderD3D9::CreateInstance();
				#else
				LFEngine::Render::GL11::LFRenderGL11::CreateInstance();  break;
				#endif
				break;

			default: LFLogger::Instance().WriteOutput("No render type defined");  break;
		}
	}

	void LFGameEngineHelper::ReleaseRender()
	{
		switch(LFRender::Instance()->RenderType())
		{
			case LFRender::RT_OpenGL11: LFEngine::Render::GL11::LFRenderGL11::ReleaseInstance(); break;

			case LFRender::RT_Direct3D9:
				#ifdef WIN32
				LFEngine::Render::D3D9::LFRenderD3D9::ReleaseInstance();
				#endif
				break;
		}
	}

	void LFGameEngineHelper::CreateRenderWindow()
	{
		#ifdef TIZEN
		LFRenderWindowTizen::CreateInstance();
		#endif

		#ifdef WIN32
		LFRenderWindowWin32::CreateInstance();
		#endif
	}

	void LFGameEngineHelper::ReleaseRenderWindow()
	{
		#ifdef TIZEN
		//LFRenderWindowTizen::ReleaseInstance(); //Tizen app holds this
		#endif

		#ifdef WIN32
		//LFRenderWindow::Instance()->AppTerminate();
		LFRenderWindowWin32::ReleaseInstance();
		#endif
	}

	void LFGameEngineHelper::CreateInput()
	{
		#ifdef TIZEN
		LFInputSystemTizen::CreateInstance();
		#endif

		#ifdef WIN32
		LFInputSystemGlfw::CreateInstance(((LFRenderWindowWin32 *)LFRenderWindow::Instance())->Window());
		#endif
	}

	void LFGameEngineHelper::ReleaseInput()
	{
		#ifdef TIZEN
		LFInputSystemTizen::ReleaseInstance();	
		#endif

		#ifdef WIN32
		LFInputSystemGlfw::ReleaseInstance();
		#endif
	}

	void LFGameEngineHelper::CreateAudio()
	{
		#ifdef TIZEN
		LFAudioSystemTizenPlayer::CreateInstance();
		#endif

		#ifdef WIN32	
		LFAudioSystemAudiere::CreateInstance();
		#endif
	}

	void LFGameEngineHelper::ReleaseAudio()
	{
		#ifdef TIZEN
		LFAudioSystemTizenPlayer::ReleaseInstance();
		#endif

		#ifdef WIN32
		LFAudioSystemAudiere::ReleaseInstance();
		#endif
	}
}}
