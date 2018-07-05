/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore
{
	class LFIOTest final
	{
	public:
		LFIOTest() = delete;
		LFIOTest(const LFIOTest &) = delete;
		LFIOTest(LFIOTest &&) = delete;
		LFIOTest &operator=(const LFIOTest &) = delete;
		LFIOTest &operator=(LFIOTest &&) = delete;
		~LFIOTest() = delete;

		static void LFSerializerStaticBinaryTest();
		static void LFSerializerDynamicBinaryTest();
		static void LFTextRWTest();
		static void LFLoggerTest();
		static void LFJsonTest();

		static void RunAllTests();
	};
}}}}
