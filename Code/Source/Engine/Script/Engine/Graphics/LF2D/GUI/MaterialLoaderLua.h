/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LFEngine { namespace GameEngine {
	class LFFontMaterial;
	class LFControlMaterial;
}}

namespace LFCore { namespace Math {
	class LFRectangle;
}}

LFEngine::GameEngine::LFFontMaterial LoadLFFontMaterial(int paramCount, int paramIndex);
LFCore::Math::LFRectangle LoadAtlas(int paramCount, int paramIndex);
LFEngine::GameEngine::LFControlMaterial LoadLFControlMaterialNAtlas(int paramCount, int paramIndexMaterial, int paramIndexAtlas);
