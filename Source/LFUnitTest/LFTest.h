/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include <list>

namespace LF3Engine { namespace LFUnitTest
{
	/**
		@brief
		Simple cross-platform unit test for TDD
	*/
	class LFTest final
	{
		static int errorCounter;
		static int tests;
		static int passedTests;
		static std::list<const char *> errorList;

	public:
		LFTest() = delete;
		LFTest(const LFTest &) = delete;
		LFTest(LFTest &&) = delete;
		LFTest &operator=(const LFTest &) = delete;
		LFTest &operator=(LFTest &&) = delete;
		~LFTest() = delete;

		static void AssertOk(bool isOk, const char *at);
		static void WriteStatistics();

		static void CoreSystemTests();
		static void DataSystemTests();
		static void NetworkSystemTests();

		static void RunAllTests();
	};
}}
