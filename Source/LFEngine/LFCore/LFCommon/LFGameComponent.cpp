/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	LFGameComponent::LFGameComponent(const LFString &name) : name(name)
	{ }

	LFString &LFGameComponent::GetName()
	{
		return name;
	}

	bool LFGameComponent::GetIsAlive() const
	{
		return isAlive;
	}

	bool LFGameComponent::GetIsVisible() const
	{
		return isVisible;
	}

	void LFGameComponent::SetIsAlive(bool isAlive)
	{
		this->isAlive = isAlive;
	}

	void LFGameComponent::SetIsVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}
}}}}