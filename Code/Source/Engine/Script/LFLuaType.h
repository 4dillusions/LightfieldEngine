/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"

namespace LFEngine { namespace Script
{
	class LFENGINE_LIBRARY LFLuaType
	{
	public:
		double number;
		bool boolean;
		char *string;
		
		void *object;
		const char *objectName;
		int objectTypeSize;

		enum LFLuaTypeEnum
		{
			LT_NUMBER,
			LT_BOOLEAN,
			LT_STRING,
			LT_OBJECT,
		};

		LFLuaTypeEnum luaTypeEnum;

		LFLuaType SetNumber(double number);
		LFLuaType SetBoolean(bool boolean);
		LFLuaType SetString(char *string);
		LFLuaType SetObject(void *object, const char *objectName, int objectTypeSize);
	};
}}
