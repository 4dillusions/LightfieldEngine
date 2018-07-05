/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest
{
	/**
		@brief
		unit test interface for basic test objects
	*/
	class LFITestObject
	{
	public:
		virtual ~LFITestObject() = default;

		virtual char GetTypeCode() = 0;
		virtual int GetId() = 0;
		virtual void SetId(int id) = 0;
	};
}}
