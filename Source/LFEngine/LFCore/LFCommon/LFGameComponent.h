/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFString.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	/**
		@brief
		for SceneGraph, Sprite and GUI elements
	*/
	class LFGameComponent
	{
		LFGameComponent(const LFGameComponent&) = delete;
		LFGameComponent(LFGameComponent &&) = delete;
		LFGameComponent &operator=(const LFGameComponent &) = delete;
		LFGameComponent &operator=(LFGameComponent &&) = delete;

	protected:
		bool isAlive = true, isVisible = true;
		LFString name;

	public:
		explicit LFGameComponent(const LFString &name);
		virtual ~LFGameComponent() = default;

		LFString &GetName();
		bool GetIsAlive() const;
		bool GetIsVisible() const;

		virtual void SetIsAlive(bool isAlive);
		virtual void SetIsVisible(bool isVisible);

		virtual void Update(double deltaTime) = 0;
	};
}}}}