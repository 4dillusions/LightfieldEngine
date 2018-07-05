/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine\LFCore\LFCommon\LFGameComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFString;
}}}}

namespace LF3Engine { namespace LFUnitTest
{
	/**
		@brief
		unit test class for Gamecomponent
	*/
	class LFTestSprite final : public LF3Engine::LFEngine::LFCore::LFCommon::LFGameComponent
	{
	public:
		static double componentUpdate;

		LFTestSprite(const LF3Engine::LFEngine::LFCore::LFCommon::LFString &name) : LFGameComponent(name)
		{ }

		//LFGameComponent interface
		void Update(double deltaTime) override
		{
			componentUpdate += deltaTime;
		}
	};

	double LFTestSprite::componentUpdate = 0;
}}
