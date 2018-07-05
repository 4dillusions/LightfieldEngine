/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSceneGraph.h"
#include "LFScreen.h"
#include "..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	LFSceneGraph::LFSceneGraph() : LFGameCompositeComponent(LFString("SceneGraph")), activeScreen(nullptr)
	{
		LFIoc<LFLogger>::Get().WriteOutput("Create SceneGraph");
	}

	LFSceneGraph::~LFSceneGraph()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release SceneGraph");
	}

	bool LFSceneGraph::GetIsActiveScreen(const LFString &name) const
	{
		if (activeScreen == nullptr)
			return false;

		return (activeScreen->GetName() == name);
	}

	LFScreen const *LFSceneGraph::GetActiveScreen() const
	{
		return activeScreen;
	}

	void LFSceneGraph::SetActiveScreen(LFScreen *screen)
	{
		if (screen != nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFString("LFSceneGraph::SetActiveScreen: ") + screen->GetName());
			activeScreen = screen;
		}
	}

	void LFSceneGraph::SetActiveScreen(const LFString &name)
	{
		LFScreen *screen = static_cast<LFScreen *>(Find(name));

		if (screen != nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFString("LFSceneGraph::SetActiveScreen: ") + name);
			activeScreen = screen;
		}
	}

	LFScreen *LFSceneGraph::FindScreen(const LFString &name)
	{
		LFGameComponent *result = Find(name);

		if (result != nullptr)
			return static_cast<LFScreen *>(result);

		return nullptr;
	}

	void LFSceneGraph::Add(LFGameComponent *screen)
	{
		LFScreen *result = dynamic_cast<LFScreen *>(screen);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFSceneGraph::Add");
			return;
		}

		LFGameCompositeComponent::Add(result);
	}

	void LFSceneGraph::Remove(LFGameComponent *screen)
	{
		LFScreen *result = dynamic_cast<LFScreen *>(screen);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFSceneGraph::Remove");
			return;
		}

		LFGameCompositeComponent::Remove(result);
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
				{
					componentList.First();
					componentList.Next();
					SetActiveScreen(static_cast<LFScreen *>(componentList.Current()));
				}
			}
		}
	}
}}}
