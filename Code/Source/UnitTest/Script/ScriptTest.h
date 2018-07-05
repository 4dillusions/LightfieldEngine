/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace UnitTest
{
	class ScriptTest
	{
    public:
		ScriptTest();
		~ScriptTest();

		void LoadTest();
		void LoadBytecodeTest();
		void GetGlobalTest(bool isTextCode = true);
		void GetGlobalBytecodeTest();
		void CppFromLuaFunctionTest(bool isTextCode = true);
		void CppFromLuaFunctionBytecodeTest();
		void MetatableTest();
	};
};
