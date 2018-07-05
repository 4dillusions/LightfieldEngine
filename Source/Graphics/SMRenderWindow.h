#pragma once

#include "FApp.h"
#include "FBase.h"
#include "FGraphics.h"
#include "FSystem.h"
#include "FUi.h"
#include "FUiControl.h"
#include "FGraphicsOpengl.h" //ogl libek: FGraphicsOpengl, FGraphicsEgl
#include "..\\Core\\SMEvent.h"
#include "..\\Core\\SMEventArgs.h"
#include "..\\Core\\SMTimer.h"
#include "..\\Engine\\SMSceneGraph.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Runtime;
using namespace Osp::Graphics::Opengl;
using namespace SMEngine::Core;
using namespace SMEngine::Engine;

namespace SMEngine { namespace Graphics
{
	class SMRenderWindow : public Application, public IScreenEventListener, public ITimerEventListener
	{
	private:
		SMRenderWindow();
		~SMRenderWindow();

		static SMRenderWindow *instance;

		Frame *frame;
		Timer *timer;
		SMTimer deltaTimer;

		EGLDisplay eglDisplay;
		EGLSurface eglSurface;
		EGLConfig eglConfig;
		EGLContext eglContext;

		int screenWidth, screenHeight;
		const int timeOut;

		SMSceneGraph *sceneGraph;

		SMAppInitTerminateEventArgs appInitTerminateEventArgs;
		SMAppForeBackGroundEventArgs appForeBackGroundEventArgs;
		SMBatteryLevelChangedEventArgs batteryLevelChangedEventArgs;
		SMAppScreenOnOffEventArgs appScreenOnOffEventArgs;

		void InitEGL();
		void InitGL();
		void Update();

	public:
		SMEventArgs<SMIAppInitTerminateEventHandler, SMAppInitTerminateEventArgs> AppInitTerminateEvent;
		SMEventArgs<SMIAppForeBackGroundEventHandler, SMAppForeBackGroundEventArgs> AppForeBackGroundEvent;
		SMEventArgs<SMIBatteryLevelChangedEventHandler, SMBatteryLevelChangedEventArgs> BatteryLevelChangedEvent;
		SMEvent<SMILowMemoryEventHandler> LowMemoryEvent;
		SMEventArgs<SMIAppScreenOnOffEventHandler, SMAppScreenOnOffEventArgs> AppScreenOnOffEvent;

		static Application *Instance() { return instance; }
		static void CreateInstance();
		static void ReleaseInstance();

		override bool OnAppInitializing(AppRegistry &appRegistry);
		override bool OnAppTerminating(AppRegistry &appRegistry, bool forcedTermination = false);
		override void OnForeground();
		override void OnBackground();
		override void OnLowMemory();
		override void OnBatteryLevelChanged(BatteryLevel batteryLevel);
		override void OnScreenOn();
		override void OnScreenOff();

		override void OnTimerExpired(Timer &timer);
	};
};};
