/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFScreen.h"
#include "LFSceneGraph.h"
#include "LFLayer.h"
#include "..\LFGUI\LFImageControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFGUI;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	LFScreen::LFScreen(const LFString &name) : LFGameCompositeComponent(name)
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("create LFScreen: ") + name);
	}

	LFScreen::~LFScreen()
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("release LFScreen: ") + name);
	}

	bool LFScreen::GetIsActive() const
	{
		return LFIoc<LFSceneGraph *>::Get()->GetIsActiveScreen(name);
	}

	void LFScreen::SetActive()
	{
		if (!GetIsActive())
			LFIoc<LFSceneGraph *>::Get()->SetActiveScreen(this);
	}

	LFLayer *LFScreen::FindLayer(const LFString &name)
	{
		LFGameComponent *result = Find(name);
		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, LFString("Does not exist! LFScreen::FindLayer ") + name);
			return nullptr;
		}

		return static_cast<LFLayer *>(result);
	}

	void LFScreen::AddBackground(const LFString &controlName, const LFString &imageName)
	{
		LFLayer *layer = FindLayer(LFString(LFSystemData::LFBackLayerName));

		if (layer == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFScreen::AddBackground");
			return;
		}

		layer->Add(LFMemoryManager::New<LFImageControl>(INFO, controlName, imageName));
	}

	void LFScreen::AddGUIObject(const LFString &layerName, LFControl *control)
	{
		LFLayer *layer = FindLayer(layerName);

		if (layer == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFScreen::AddGUIObject");
			return;
		}

		control->SetScreen(this);
		layer->Add(control);
	}

	void LFScreen::Add(LFGameComponent *layer)
	{
		LFLayer *result = dynamic_cast<LFLayer *>(layer);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFScreen::Add");
			return;
		}

		LFGameCompositeComponent::Add(result);
		result->SetScreen(this);
	}

	void LFScreen::Remove(LFGameComponent *layer)
	{
		LFLayer *result = dynamic_cast<LFLayer *>(layer);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFScreen::Remove");
			return;
		}

		LFGameCompositeComponent::Remove(result);
	}
}}}
