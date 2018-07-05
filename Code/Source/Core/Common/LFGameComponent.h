/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFString.h"

namespace LFCore { namespace Common
{
	class LFCORE_LIBRARY LFGameComponent
	{
	protected:
		bool isAlive, isVisible;
		LFString name;

	public:
		explicit LFGameComponent(const LFString &name) : isAlive(true), isVisible(true), name(name)
		{ }

		virtual ~LFGameComponent()
		{ }

		LFString &GetName() { return name; }
		bool GetIsAlive() { return isAlive; }
		bool GetIsVisible() { return isVisible; }

		virtual void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
		virtual void SetIsVisible(bool isVisible) { this->isVisible = isVisible; }

		virtual void Update(double deltaTime) = 0;
	};
}}
