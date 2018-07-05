/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore 
{
	class LFCollectionsTest final
	{
	public:
		LFCollectionsTest() = delete;
		LFCollectionsTest(const LFCollectionsTest &) = delete;
		LFCollectionsTest(LFCollectionsTest &&) = delete;
		LFCollectionsTest &operator=(const LFCollectionsTest &) = delete;
		LFCollectionsTest &operator=(LFCollectionsTest &&) = delete;
		~LFCollectionsTest() = delete;

		static void LFLinkedListNodeTest();
		static void LFLinkedListTest();
		static void LFListNodeTest();
		static void LFListTest();
		static void LFDictionaryNodeTest();
		static void LFDictionaryTest();

		static void RunAllTests();
	};
}}}}
