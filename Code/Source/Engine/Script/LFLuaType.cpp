/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLuaType.h"

namespace LFEngine { namespace Script
{	
	LFLuaType LFLuaType::SetNumber(double number)
	{
		luaTypeEnum = LT_NUMBER;
		this->number = number;
		
		return *this;
	}

	LFLuaType LFLuaType::SetBoolean(bool boolean)
	{
		luaTypeEnum = LT_BOOLEAN;
		this->boolean = boolean;
		
		return *this;
	}

	LFLuaType LFLuaType::SetString(char *string)
	{
		luaTypeEnum = LT_STRING;
		this->string = string;
		
		return *this;
	}

	LFLuaType LFLuaType::SetObject(void *object, const char *objectName, int objectTypeSize)
	{
		luaTypeEnum = LT_OBJECT;
		this->object = object;
		this->objectName = objectName;
		this->objectTypeSize = objectTypeSize;
		
		return *this;
	}
}}
