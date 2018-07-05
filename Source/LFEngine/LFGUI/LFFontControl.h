/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFFontControl : public LFControl
	{
	public:
		LFFontControl(const LFCore::LFCommon::LFString &name, char character, const LFCore::LFMath::LFRectangle &posSize);
		virtual ~LFFontControl() = default;

		void SetCharacter(char character);
	};
}}}
