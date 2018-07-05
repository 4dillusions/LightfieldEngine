#include "SMRenderWindow.h"
#include "..\\Input\\SMInput.h"
#include "..\\Audio\\SMAudio.h"
#include "..\\IO\\SMLogger.h"

using namespace SMEngine::Input;
using namespace SMEngine::Audio;
using namespace SMEngine::IO;

namespace SMEngine { namespace Graphics
{
	SMRenderWindow *SMRenderWindow::instance = nullptr;

	SMRenderWindow::SMRenderWindow() :
        AppInitTerminateEvent(&SMIAppInitTerminateEventHandler::InitTerminateChanged),
		AppForeBackGroundEvent(&SMIAppForeBackGroundEventHandler::ForeBackGroundChanged),
		BatteryLevelChangedEvent(&SMIBatteryLevelChangedEventHandler::BatteryLevelChanged),
		LowMemoryEvent(&SMILowMemoryEventHandler::LowMemory),
		AppScreenOnOffEvent(&SMIAppScreenOnOffEventHandler::ScreenOnOffChanged),
		frame(nullptr), timer(nullptr), sceneGraph(nullptr), timeOut(10)
	{ }

	SMRenderWindow::~SMRenderWindow()
	{ }

	void SMRenderWindow::CreateInstance()
	{
		if (instance == nullptr)
			instance = new SMRenderWindow();
	}

	void SMRenderWindow::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			instance->timer->Cancel();

			delete instance;
			instance = nullptr;
		}
	}

	void SMRenderWindow::InitEGL()
	{
		eglBindAPI(EGL_OPENGL_ES_API);
		EGLint numConfigs = 1;

		EGLint eglConfigList[] =
		{
			EGL_RED_SIZE, 6,
			EGL_GREEN_SIZE, 6,
			EGL_BLUE_SIZE, 6,
			EGL_RENDERABLE_TYPE,
			EGL_OPENGL_ES_BIT,
			EGL_SURFACE_TYPE,
			EGL_WINDOW_BIT,
			EGL_NONE
		};

		eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
		eglInitialize(eglDisplay, 0, 0);
		eglChooseConfig(eglDisplay, eglConfigList, &eglConfig, 1, &numConfigs);
		eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)GetAppFrame()->GetFrame(), 0);
		eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, 0);
		eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	}

	void SMRenderWindow::InitGL()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		int x, y;
		frame->GetBounds(x, y, screenWidth, screenHeight);
		glViewport(x, y, screenWidth, screenHeight);
		glScalef(1.0f / screenWidth, 1.0f / screenHeight, 0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClearColor(0.0f, 255.0f, 0.0f, 0.0f); //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glShadeModel(GL_FLAT); //polygononkénti szín, nincs gouraud árnyalás
		glEnable(GL_CULL_FACE); //triviális hátsólap eldobás
		glCullFace(GL_FRONT);
		glDisable(GL_DEPTH_TEST); //z-buffer
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0); //csak a 0 alfájú színek lesznek eldobva
		glDisable(GL_DITHER); //a megjeleníthetõ színek számát a felbontás rovására ne növelje
	}

	void SMRenderWindow::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		sceneGraph->Update(deltaTimer.DeltaTime());
		eglSwapBuffers(eglDisplay, eglSurface);
	}

	bool SMRenderWindow::OnAppInitializing(AppRegistry &appRegistry)
	{
		frame = Application::GetInstance()->GetAppFrame()->GetFrame();

		InitEGL();
		InitGL();

		timer = new Timer();
		timer->Construct(*this);

		appInitTerminateEventArgs.applicationState = SMAppInitTerminateEventArgs::INITIALIZING;
		AppInitTerminateEvent(appInitTerminateEventArgs);

		sceneGraph = SMSceneGraph::Instance();

		return true;
	}

	bool SMRenderWindow::OnAppTerminating(AppRegistry &appRegistry, bool forcedTermination)
	{
		appInitTerminateEventArgs.applicationState = SMAppInitTerminateEventArgs::TERMINATE;
		AppInitTerminateEvent(appInitTerminateEventArgs);

		return true;
	}

	void SMRenderWindow::OnForeground()
	{
		deltaTimer.Reset();
		timer->Start(timeOut);
		SMAudio::Instance()->PlayAllSound();

		appForeBackGroundEventArgs.groundState = SMAppForeBackGroundEventArgs::FOREGROUND;
		AppForeBackGroundEvent(appForeBackGroundEventArgs);
	}

	void SMRenderWindow::OnBackground()
	{
		timer->Cancel();
		SMAudio::Instance()->PauseAllSound();

		appForeBackGroundEventArgs.groundState = SMAppForeBackGroundEventArgs::BACKGROUND;
		AppForeBackGroundEvent(appForeBackGroundEventArgs);
	}

	void SMRenderWindow::OnLowMemory()
	{
		LowMemoryEvent();
	}

	void SMRenderWindow::OnBatteryLevelChanged(BatteryLevel batteryLevel)
	{
		switch(batteryLevel)
		{
			case BATTERY_FULL: batteryLevelChangedEventArgs.batteryLevel = SMBatteryLevelChangedEventArgs::BATTERY_FULL; break;
			case BATTERY_HIGH: batteryLevelChangedEventArgs.batteryLevel = SMBatteryLevelChangedEventArgs::BATTERY_HIGH; break;
			case BATTERY_LOW: batteryLevelChangedEventArgs.batteryLevel = SMBatteryLevelChangedEventArgs::BATTERY_LOW; break;
			case BATTERY_CRITICAL: batteryLevelChangedEventArgs.batteryLevel = SMBatteryLevelChangedEventArgs::BATTERY_CRITICAL; break;
			case BATTERY_EMPTY: batteryLevelChangedEventArgs.batteryLevel = SMBatteryLevelChangedEventArgs::BATTERY_EMPTY; break;
		}

		BatteryLevelChangedEvent(batteryLevelChangedEventArgs);
	}

	void SMRenderWindow::OnScreenOn()
	{
		appScreenOnOffEventArgs.screenState = SMAppScreenOnOffEventArgs::ON;
		AppScreenOnOffEvent(appScreenOnOffEventArgs);
	}

	void SMRenderWindow::OnScreenOff()
	{
		appScreenOnOffEventArgs.screenState = SMAppScreenOnOffEventArgs::OFF;
		AppScreenOnOffEvent(appScreenOnOffEventArgs);
	}

	void SMRenderWindow::OnTimerExpired(Timer &timer)
	{
		this->timer->Start(timeOut);
		Update();
	}
};};
