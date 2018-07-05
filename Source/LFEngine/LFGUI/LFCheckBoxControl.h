/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFTouchableControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFCheckBoxControl final : public LFTouchableControl
	{
		bool isChecked;

		void ChangeColor(bool isPressed) override;

	public:
		LFCheckBoxControl(const LFCore::LFCommon::LFString &name, const LFCore::LFMath::LFRectangle &posTileSize, bool isChecked,
			const LFCore::LFMath::LFVector2D &posAtlasChecked, const LFCore::LFMath::LFVector2D &posAtlasUnchecked);
		~LFCheckBoxControl() = default;

		bool GetIsChecked() const;
		void SetIsChecked(bool isChecked);

		//LFControl functions
		void SetIsVisible(bool isVisible) override;
	};
}}}
