/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCollections\LFList.h"
#include "..\..\LFCore\LFCommon\LFString.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO 
{
	struct LFJSonPair { LFCommon::LFString key; LFCommon::LFString value; };

	/**
		@brief
		Read or Write Json format
	*/
	class LFJson final
	{
		LFJson() = delete;
		LFJson(const LFJson&) = delete;
		LFJson(LFJson &&) = delete;
		LFJson &operator=(const LFJson &) = delete;
		LFJson &operator=(LFJson &&) = delete;

	public:
        static LFCommon::LFString CreateObjectPairs(LFCollections::LFList<LFJSonPair> &pairs);
		static LFJSonPair GetObjectPair(const LFCommon::LFString &jsonPair);
		static LFCollections::LFList<LFCollections::LFList<LFJSonPair>> GetArrayPairs(const LFCommon::LFString &jsonArray);
	};
}}}}
