#pragma once

#include "LFLabelControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI {
	class LFENGINE_LIBRARY LFNumberLabelControl : public LFLabelControl
	{
	private:
		LFCore::Common::LFString valueText;

	public:
		LFNumberLabelControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFLabelData &labelData);
		virtual ~LFNumberLabelControl();

		int Value() { return labelData.text.ToInt(); }
		void Value(int value);
	};
}}}}
