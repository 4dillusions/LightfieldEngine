#pragma once

#include "..\\Graphics\\SMRenderWindow.h"
#include "..\\Input\\SMInput.h"
#include "..\\Audio\\SMAudio.h"

using namespace SMEngine::Graphics;
using namespace SMEngine::Input;
using namespace SMEngine::Audio;

namespace SMEngine { namespace Engine
{
	class SMMainEngine : SMIAppInitTerminateEventHandler
	{
	private:
		SMMainEngine();
		~SMMainEngine();

		static SMMainEngine *instance;
		SMRenderWindow *renderWindow;

	public:
		static void CreateInstance();
		static void ReleaseInstance();

		static SMMainEngine *Instance() { return instance; }
		SMRenderWindow *RenderWindow() { return renderWindow; }

		virtual void InitTerminateChanged(const SMAppInitTerminateEventArgs &args);
		void WriteReport();
		void Exit();
	};
};};
