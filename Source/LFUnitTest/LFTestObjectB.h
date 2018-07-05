/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFITestObject.h"
#include "..\LFEngine\LFCore\LFCommon\LFEvent.h"

namespace LF3Engine { namespace LFUnitTest 
{
	class Args final
	{
	public:
		int x;
	};

	class LFTestObjectB final : public LFITestObject
	{
		int id = 0;

	public:
		LF3Engine::LFEngine::LFCore::LFCommon::LFEvent<Args> TestEvent;
		void PerformTestEvent(Args args);

		char GetTypeCode() override;
		int GetId() override;
		void SetId(int id) override;
	};
}}
