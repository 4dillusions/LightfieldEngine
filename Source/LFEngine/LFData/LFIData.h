/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	class LFIData
	{
	public:
		LFIData(const LFIData&) = delete;
		LFIData(LFIData &&) = delete;
		LFIData &operator=(const LFIData &) = delete;
		LFIData &operator=(LFIData &&) = delete;

		LFIData() = default;
		virtual ~LFIData() = default;

		virtual void Reset() = 0;
		virtual bool Load() = 0; //open from VFS
		virtual bool Load(const char *fileName) = 0; //open from file somwhere
		virtual void Save() = 0; //save to VFS
		virtual void Save(const char *fileName) = 0; //save to file somwhere
	};
}}}
