/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFScreen.h"
#include "LFSceneGraph.h"
#include "LFLayer.h"
#include "..\..\Core\\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace GameEngine
{
    LFScreen::LFScreen(const LFString &name) : LFGameCompositComponent(name)
    { }

	LFScreen::~LFScreen()
    { }

	bool LFScreen::IsActive()
	{
		return LFSceneGraph::Instance()->IsActiveScreen(name);
	}

	void LFScreen::SetActive()
	{
		LFSceneGraph::Instance()->ActiveScreen(this);
	}

	LFLayer *LFScreen::FindLayer(const LFString &name)
	{
		LFGameComponent *result = Find(name);

		if (result != nullptr)
			return (LFLayer *)result;

		return nullptr;
	}

	void LFScreen::Add(LFGameComponent *lFLayer)
	{
		LFLayer *layer = dynamic_cast<LFLayer *>(lFLayer);

		if (layer == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LFScreen::Add");
			return;
		}

		LFGameCompositComponent::Add(layer);
		layer->Screen(this);
	}

	void LFScreen::Remove(LFGameComponent *lFLayer)
	{
		LFLayer *layer = dynamic_cast<LFLayer *>(lFLayer);

		if (layer == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LFScreen::Remove");
			return;
		}

		LFGameCompositComponent::Remove(layer);
	}
}}
