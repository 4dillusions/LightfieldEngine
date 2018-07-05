/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFITestObject.h"

namespace LF3Engine { namespace LFUnitTest
{
	class LFTestObjectA final : public LFITestObject
	{
		static int referenceCounter;
		int id = 0;

	public:
		LFTestObjectA();
		LFTestObjectA(const LFTestObjectA &value);
		~LFTestObjectA();

		LFTestObjectA &operator = (const LFTestObjectA &value) = default;

		char GetTypeCode() override;
		int GetId() override;
		void SetId(int id) override;

		static int GetReferenceCounter();
		static void SetReferenceCounter(int counter);
	};
}}
