/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LFCore { namespace Common
{
	class LFString;
}}

namespace UnitTest
{
	class Test
	{
    private:
        static int errorCounter;

    public:
		static void PushErrorCounts(int errorCounter);
        static void AssertOk(bool isOk, const char *description);
		static void Write(LFCore::Common::LFString &description);
        static void WriteStatistics();

        static void CoreSystemTest();
		static void ScriptSystemTest();
	};
}
