/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"

namespace LFEngine { namespace Data
{
	class LFENGINE_LIBRARY LFIData
	{
	public:
		virtual ~LFIData() { };

		virtual void Reset() = 0;
		virtual bool Load() = 0; //open from VFS
		virtual bool Load(const char *fileName) = 0; //open from file somwhere
		virtual void Save() = 0; //save to VFS
		virtual void Save(const char *fileName) = 0; //save to file somwhere
	};
}}
