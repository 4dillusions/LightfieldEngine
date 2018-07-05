/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTestObjectB.h"

namespace LF3Engine { namespace LFUnitTest
{
	void LFTestObjectB::PerformTestEvent(Args args)
	{
		TestEvent(args);
	}

	char LFTestObjectB::GetTypeCode()
	{
		return 'B';
	}

	int LFTestObjectB::GetId()
	{
		return id;
	}

	void LFTestObjectB::SetId(int id)
	{
		this->id = id;
	}
}}
