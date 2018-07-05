/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFFontControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFLabelControl : public LFFontControl
	{
		LFCore::LFCommon::LFString text;

	public:
		LFLabelControl(const LFCore::LFCommon::LFString &name, const LFCore::LFCommon::LFString &text, const LFCore::LFMath::LFRectangle &posTileSize);
		virtual ~LFLabelControl() = default;

		virtual int GetTextLength() const;

		void SetText(const LFCore::LFCommon::LFString &text);
		const LFCore::LFCommon::LFString &GetText() const;

		//LFControl functions
		void SetColor(const LFCore::LFMath::LFColor &color) override;
	};
}}}
