/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore 
{
	class LFPatternsTest final
	{
	public:
		LFPatternsTest() = delete;
		LFPatternsTest(const LFPatternsTest &) = delete;
		LFPatternsTest(LFPatternsTest &&) = delete;
		LFPatternsTest &operator=(const LFPatternsTest &) = delete;
		LFPatternsTest &operator=(LFPatternsTest &&) = delete;
		~LFPatternsTest() = delete;

		static void LFIocTest();

		static void RunAllTests();
	};
}}}}
