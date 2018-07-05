/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore 
{
	class LFCommonTest final
	{
	public:
		LFCommonTest() = delete;
		LFCommonTest(const LFCommonTest &) = delete;
		LFCommonTest(LFCommonTest &&) = delete;
		LFCommonTest &operator=(const LFCommonTest &) = delete;
		LFCommonTest &operator=(LFCommonTest &&) = delete;
		~LFCommonTest() = delete;

		static void LFTupleTest();
		static void LFMemoryManagerTest();
		static void LFStringTest();
		static void LFVFSManagerTest();
		static void LFGameComponentTest();
		static void LFGameCompositeComponentTest();
		static void LFTimerTest();
		static void LFWatchTest();
		static void LFEventTest();

		static void RunAllTests();
	};
}}}}
