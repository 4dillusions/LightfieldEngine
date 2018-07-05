/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFNetwork
{
	class LFNetworkTest final
	{
	public:
		LFNetworkTest() = delete;
		LFNetworkTest(const LFNetworkTest &) = delete;
		LFNetworkTest(LFNetworkTest &&) = delete;
		LFNetworkTest &operator=(const LFNetworkTest &) = delete;
		LFNetworkTest &operator=(LFNetworkTest &&) = delete;
		~LFNetworkTest() = delete;

		static void LFCurlBasicTest();
		static void LFCurlMySQLTest();
		
		static void RunAllTests();
	};
}}}}
