/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LF3GameEngineFactory.h"
#include "..\LFRender\LFRenderComponentList.h"
#include "..\..\LFEngine\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"
#include "..\..\LFEngine\LFRender\LFIRenderSystem.h"
#include "..\..\LFEngine\LFRender\LFRenderWindow.h"
#include "..\..\LFEngine\LFRender\_Win32_\LFRenderWindowWin32.h"
#include "..\..\LFEngine\LFRender\_Tizen_\LFRenderWindowTizen.h"
#include "..\..\LFEngine\LFRender\LFGLES20\LFRenderSystemGLES20.h"
#include "..\..\LFEngine\LFRender\_Win32_\LFD3D9\LFRenderSystemD3D9.h"
#include "..\..\LFEngine\LFInput\LFInputSystem.h"
#include "..\..\LFEngine\LFInput\_Tizen_\LFInputSystemTizen.h"
#include "..\..\LFEngine\LFInput\_Win32_\LFInputSystemWin32.h"
#include "..\..\LFEngine\LFAudio\LFAudioSystem.h"
#include "..\..\LFEngine\LFAudio\_Tizen_\LFAudioSystemTizen.h"
#include "..\..\LFEngine\LFAudio\_Win32_\LFAudioSystemWin32.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFRender;
using namespace LF3Engine::LFEngine::LFInput;
using namespace LF3Engine::LFEngine::LFAudio;
using namespace LFGLES20;

#ifndef TIZEN
	using namespace LFD3D9;
#endif

namespace LF3Engine { namespace LFEngine { namespace LFGameEngine
{
	void LF3GameEngineFactory::CreateRenderSystem()
	{
		#ifdef WINCLASSIC
			if (LFString(LFSystemData::LFRender) == LFString("Direct3D9"))
				LFIoc<LFIRenderSystem *>::Register<LFRenderSystemD3D9>();
			else if (LFString(LFSystemData::LFRender) == LFString("OpenGL20"))
				LFIoc<LFIRenderSystem *>::Register<LFRenderSystemGLES20>();
			else
			{
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Wrong render type defined!");
				return;
			}
		#endif

		#ifdef TIZEN
			LFIoc<LFIRenderSystem *>::Register<LFRenderSystemGLES20>();
		#endif

		LFIoc<LFIRenderSystem *>::Create();
	}

	void LF3GameEngineFactory::ReleaseRenderSystem()
	{
		LFIoc<LFIRenderSystem *>::Release();
	}

	void LF3GameEngineFactory::CreateRenderComponentList()
	{
		LFIoc<LFRenderComponentList *>::Register<LFRenderComponentList>();
		LFIoc<LFRenderComponentList *>::Create();
	}

	void LF3GameEngineFactory::ReleaseRenderComponentList()
	{
		LFIoc<LFRenderComponentList *>::Get()->ReleaseAll();
		LFIoc<LFRenderComponentList *>::Release();
	}

	void LF3GameEngineFactory::CreateRenderWindow()
	{
		#ifdef WINCLASSIC
            LFIoc<LFRenderWindow *>::Register<LFRenderWindowWin32>();
		#endif

		#ifdef TIZEN
			LFIoc<LFRenderWindow *>::Register<LFRenderWindowTizen>();
		#endif

		LFIoc<LFRenderWindow *>::Create();
	}

	void LF3GameEngineFactory::ReleaseRenderWindow()
	{
		LFIoc<LFRenderWindow *>::Release();
	}

	void LF3GameEngineFactory::CreateInput()
	{
		#ifdef WINCLASSIC
			LFIoc<LFInputSystem *>::Register<LFInputSystemWin32>();
		#endif

		#ifdef TIZEN
			LFIoc<LFInputSystem *>::Register<LFInputSystemTizen>();
		#endif

		LFIoc<LFInputSystem *>::Create();
	}

	void LF3GameEngineFactory::ReleaseInput()
	{
		LFIoc<LFInputSystem *>::Release();
	}

	void LF3GameEngineFactory::CreateAudio()
	{
		#ifdef WINCLASSIC
			LFIoc<LFAudioSystem *>::Register<LFAudioSystemWin32>();
		#endif

		#ifdef TIZEN
			LFIoc<LFAudioSystem *>::Register<LFAudioSystemTizen>();
		#endif

		LFIoc<LFAudioSystem *>::Create();
	}

	void LF3GameEngineFactory::ReleaseAudio()
	{
		LFIoc<LFAudioSystem *>::Release();
	}
}}}
