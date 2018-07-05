/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFImageControl final : public LFControl
	{
	public:
		LFImageControl(const LFCore::LFCommon::LFString &name, const LFCore::LFCommon::LFString &textureName);
		~LFImageControl() = default;
	};
}}}
