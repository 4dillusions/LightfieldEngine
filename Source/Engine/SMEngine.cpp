#include "SMEngine.h"
#include "..\\Graphics\\SMTextureManager.h"
#include "..\\Graphics\\SMVertexBufferManager.h"
#include "..\\IO\\SMLogger.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Engine
{
	SMMainEngine *SMMainEngine::instance = nullptr;

	SMMainEngine::SMMainEngine()
	{
		SMRenderWindow::CreateInstance();
		renderWindow = (SMRenderWindow *)SMRenderWindow::Instance();
		renderWindow->AppInitTerminateEvent += this;
	}

	SMMainEngine::~SMMainEngine()
	{
		//TODO: content leak
		//renderWindow->AppInitTerminateEvent -= this;
		//SMRenderWindow::ReleaseInstance();
	}

	void SMMainEngine::CreateInstance()
	{
		if (instance == nullptr)
			instance = new SMMainEngine();
	}

	void SMMainEngine::InitTerminateChanged(const SMAppInitTerminateEventArgs &args)
	{
		if (args.applicationState == SMAppInitTerminateEventArgs::INITIALIZING)
		{
			SMInput::CreateInstance();
			SMAudio::CreateInstance();
			SMTextureManager::CreateInstance();
			SMVertexBufferManager::CreateInstance();
			SMSceneGraph::CreateInstance();
		}
	}

	void SMMainEngine::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			instance->WriteReport();

			SMInput::ReleaseInstance();
			SMAudio::ReleaseInstance();
			SMSceneGraph::ReleaseInstance();
			SMTextureManager::ReleaseInstance();
			SMVertexBufferManager::ReleaseInstance();

			delete instance;
			instance = nullptr;
		}
	}

	void SMMainEngine::WriteReport()
	{
		SMLogger::Instance().WriteOutput("Content report");

		SMTextureManager::Instance()->WriteReport();
		SMLogger::Instance().WriteOutput("");

		SMVertexBufferManager::Instance()->WriteReport();
		SMLogger::Instance().WriteOutput("");

		SMSceneGraph::Instance()->WriteReport();
		SMLogger::Instance().WriteOutput("");
	}

	void SMMainEngine::Exit()
	{
		Application::GetInstance()->Terminate();
	}
};};
