/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\GameEngine\LFControl.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\\Math\LFRectangle.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;
using namespace LFCore::Math;

void LoadLFMaterial(int paramCount, int paramIndex, LFMaterial *result)
{
	result->textureName = LFScriptSystem::Instance()->GetMetatableParameterValue("textureName", paramCount, paramIndex, LFLuaType::LT_STRING).string;
	result->textureWidth = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("textureWidth", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
	result->textureHeight = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("textureHeight", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
	result->atlasWidth = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("atlasWidth", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
	result->atlasHeight = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("atlasHeight", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
}

LFFontMaterial LoadLFFontMaterial(int paramCount, int paramIndex)
{
	LFFontMaterial result;

	LoadLFMaterial(paramCount, paramIndex, &result);

	result.alphabet = LFScriptSystem::Instance()->GetMetatableParameterValue("alphabet", paramCount, paramIndex, LFLuaType::LT_STRING).string;
	result.alphabetSize = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("alphabetSize", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;

	int alphabetCounter = 0;
	for (int y = 0; y < result.atlasHeight; ++y)
		for (int x = 0; x < result.atlasWidth && alphabetCounter < result.alphabetSize; ++x, ++alphabetCounter)
		{
			result.alphabetData[(int)result.alphabet[alphabetCounter]].x = (float)x;
			result.alphabetData[(int)result.alphabet[alphabetCounter]].y = (float)y;
		}

	return result;
}

LFRectangle LoadAtlas(int paramCount, int paramIndex)
{
	LFRectangle result;

	result.position.x = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
	result.position.y = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
	result.width = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("sizeX", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;
	result.height = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("sizeY", paramCount, paramIndex, LFLuaType::LT_NUMBER).number;

	return result;
}

LFControlMaterial LoadLFControlMaterialNAtlas(int paramCount, int paramIndexMaterial, int paramIndexAtlas)
{
	LFControlMaterial result;

	//#1 table parameter: control material
	LoadLFMaterial(paramCount, paramIndexMaterial, &result);

	//#2 table parameter: atlas
	result.atlasPosSize = LoadAtlas(paramCount, paramIndexAtlas);

	return result;
}
