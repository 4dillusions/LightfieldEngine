#include "LFNumberLabelControl.h"
#include "LFLabelControl.h"
#include "LFSpriteFont.h"
#include "..\..\..\Script\LFLuaType.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFNumberLabelControlLua.h"
#include "..\..\..\..\Core\\Math\LFVector2D.h"

using namespace LFEngine::Script;
using namespace LFCore::Common;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI {
	LFNumberLabelControl::LFNumberLabelControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFLabelData &labelData) : LFLabelControl(fontMaterial, labelData)
	{ 
		controlType = LFLuaType().SetObject(this, LFNumberLabelControlName, sizeof(LFNumberLabelControl));
	}

	LFNumberLabelControl::~LFNumberLabelControl()
	{ }

	void LFNumberLabelControl::Value(int value)
	{
		labelData.text = LFString().AppendStr(value, labelData.digits);

		int i = 0;
		for (componentList.First(); componentList.IsDone(); componentList.Next(), ++i)
			((LFSpriteFont *)componentList.Current())->Character(labelData.text[i], fontMaterial.GetAtlasPos(labelData.text[i]));
	}
}}}}
