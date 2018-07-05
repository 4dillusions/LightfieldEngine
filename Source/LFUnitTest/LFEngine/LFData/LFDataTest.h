/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFData
{
	class LFDataTest final
	{
	public:
		LFDataTest() = delete;
		LFDataTest(const LFDataTest &) = delete;
		LFDataTest(LFDataTest &&) = delete;
		LFDataTest &operator=(const LFDataTest &) = delete;
		LFDataTest &operator=(LFDataTest &&) = delete;
		~LFDataTest() = delete;

		static void LFGameStateTest();
		static void LFLevelDataTest();
		static void LFOptionsDataTest();

		static void RunAllTests();
	};
}}}}
