/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRenderComponent.h"
#include "..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFRenderComponent::LFRenderComponent(const LFString &name)
		: name(name)
	{
		vfsManager = LFCore::LFPatterns::LFIoc<LFVFSManager *>::Get();
	}

	const LFString &LFRenderComponent::GetName() const
	{
		return name;
	}
}}}
