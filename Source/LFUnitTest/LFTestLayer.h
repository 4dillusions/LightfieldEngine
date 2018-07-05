/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine\LFCore\LFCommon\LFGameCompositeComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFString;
}}}}

namespace LF3Engine { namespace LFUnitTest
{
	/**
		@brief
		unit test class for GameCompositeComponent
	*/
	class LFTestLayer final : public LF3Engine::LFEngine::LFCore::LFCommon::LFGameCompositeComponent
	{
	public:
		LFTestLayer(const LF3Engine::LFEngine::LFCore::LFCommon::LFString &name) : LFGameCompositeComponent(name)
		{ }
	};
}}
