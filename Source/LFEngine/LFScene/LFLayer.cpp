/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLayer.h"
#include "..\LFGUI\LFControl.h"
#include "..\LFRender\LFShaderEffect.h"
#include "..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFGUI;
using namespace LF3Engine::LFEngine::LFRender;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	LFLayer::LFLayer(const LFString &name) : LFGameCompositeComponent(name), screen(nullptr)
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("create LFLayer: ") + name);
	}

	LFLayer::~LFLayer()
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("release LFLayer: ") + name);
	}

	LFScreen *LFLayer::GetScreen() const
	{
		return screen;
	}

	void LFLayer::SetScreen(LFScreen *screen)
	{
		this->screen = screen;
	}

	LFControl *LFLayer::FindControl(const LFString &name)
	{
		LFGameComponent *result = Find(name);
		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, LFString("Does not exist! LFLayer::FindControl ") + name);
			return nullptr;
		}

		return static_cast<LFControl *>(result);
	}

	void LFLayer::Add(LFGameComponent *control)
	{
		LFControl *result = dynamic_cast<LFControl *>(control);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFLayer::Add");
			return;
		}

		if (auto ctrl = dynamic_cast<LFControl *>(control))
			if (shader == nullptr && ctrl->GetIsRenderable())
				shader = ctrl->GetShader();

		LFGameCompositeComponent::Add(result);
	}

	void LFLayer::Remove(LFGameComponent *control)
	{
		LFControl *result = dynamic_cast<LFControl *>(control);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFLayer::Remove");
			return;
		}

		LFGameCompositeComponent::Remove(result);
	}

	void LFLayer::Update(double deltaTime)
	{
		if (shader != nullptr)
		{
			shader->BeginRender();
			LFGameCompositeComponent::Update(deltaTime);
			shader->EndRender();
		}
	}
}}}
