/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTestObjectA.h"

namespace LF3Engine { namespace LFUnitTest
{
	int LFTestObjectA::referenceCounter = 0;

	LFTestObjectA::LFTestObjectA()
	{
		referenceCounter++;
	}

	LFTestObjectA::LFTestObjectA(const LFTestObjectA &value)
	{
		referenceCounter++;
	}

	LFTestObjectA::~LFTestObjectA()
	{
		referenceCounter--;
	}

	char LFTestObjectA::GetTypeCode()
	{
		return 'A';
	}

	int LFTestObjectA::GetId()
	{
		return id;
	}

	void LFTestObjectA::SetId(int id)
	{
		this->id = id;
	}

	int LFTestObjectA::GetReferenceCounter()
	{
		return referenceCounter;
	}

	void LFTestObjectA::SetReferenceCounter(int counter)
	{
		referenceCounter = counter;
	}
}}
