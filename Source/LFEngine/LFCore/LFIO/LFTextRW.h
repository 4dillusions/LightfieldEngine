/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
    class LFString;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO
{
	class LFTextRW final
	{
		LFTextRW(const LFTextRW &) = delete;
		LFTextRW(LFTextRW &&) = delete;
		LFTextRW& operator=(const LFTextRW &) = delete;
		LFTextRW& operator=(LFTextRW &&) = delete;

	public:
		LFTextRW() = default;
		~LFTextRW() = default;

		LFCommon::LFString Read(const LFCommon::LFString &pathAndName) const;
	};
}}}}
