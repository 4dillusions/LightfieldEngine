/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSceneGraph.h"
#include "LFScreen.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\IO\LFLogger.h"
#include "..\..\Core\Common\LFGameComponent.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace GameEngine
{
	LFSceneGraph *LFSceneGraph::instance = nullptr;

    LFSceneGraph::LFSceneGraph() : LFGameCompositComponent(LFString("SceneGraph")), activeScreen(nullptr)
    { }

    LFSceneGraph::~LFSceneGraph()
    { }

    void LFSceneGraph::CreateInstance()
    {
    	if (instance == nullptr)
		{
			instance = LFNew<LFSceneGraph>(AT);
			LFLogger::Instance().WriteOutput("Init SceneGraph");
		}
    }

    void LFSceneGraph::ReleaseInstance()
    {
        if (instance != nullptr)
		{
			LFLogger::Instance().WriteOutput("Release SceneGraph");
			LFDelete(instance);
		}
    }

	bool LFSceneGraph::IsActiveScreen(const LFCore::Common::LFString &name)
	{
		if (activeScreen == nullptr)
			return false;

		return (activeScreen->GetName() == name);
	}

    void LFSceneGraph::ActiveScreen(const LFString &name)
    {
    	LFScreen *screen = (LFScreen *)Find(name);

    	if (screen != nullptr)
    		activeScreen = screen;
    }

	LFScreen *LFSceneGraph::FindScreen(const LFString &name)
	{
		LFGameComponent *result = Find(name);

		if (result != nullptr)
			return (LFScreen *)result;

		return nullptr;
	}

	void LFSceneGraph::Add(LFGameComponent *lFScreen)
	{
		LFScreen *screen = dynamic_cast<LFScreen *>(lFScreen);

		if (screen == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LFSceneGraph::Add");
			return;
		}

		LFGameCompositComponent::Add(screen);
		activeScreen = screen;
	}

    void LFSceneGraph::Remove(LFGameComponent *lFScreen)
    {
    	LFScreen *screen = dynamic_cast<LFScreen *>(lFScreen);

		if (screen == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LFSceneGraph::Remove");
			return;
		}

    	LFGameCompositComponent::Remove(screen);
    }

	void LFSceneGraph::Update(double deltaTime)
	{
		if (activeScreen != nullptr)
		{
			if (activeScreen->GetIsAlive())
				activeScreen->Update(deltaTime);
			else
			{
				componentList.Delete(activeScreen);
				activeScreen = nullptr;

				if (componentList.Length() > 0)
					activeScreen = (LFScreen *)componentList.GetFirst();
			}
		}
    }
}}
