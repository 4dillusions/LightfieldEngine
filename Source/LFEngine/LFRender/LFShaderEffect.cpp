/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFShaderEffect.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFIO\LFLogger.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFShaderEffect::LFShaderEffect(const LFString &effectName, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFRenderComponent(effectName), keyName(""), textureName(textureName), vertexTextureDataName(""), vertexSize(vertexSize), atlasSize(atlasSize)
	{ }

	LFString LFShaderEffect::GenerateKeyName(const LFString &shaderName, const LFString &textureName, const LFString &vertexTextureDataName)
	{
		return shaderName + "_" + textureName + "_" + vertexTextureDataName;
	}

	const LFString &LFShaderEffect::GetKeyName()
	{
		if (keyName.IsEmpty())
			keyName = GenerateKeyName(name, textureName, vertexTextureDataName);

		return keyName;
	}

	void LFShaderEffect::SetRelativePosition(const LFVector2D &relativePosition)
	{
		this->relativePosition = relativePosition;
	}

	void LFShaderEffect::SetColor(const LFColor & color)
	{
		this->color = color;
	}

	void LFShaderEffect::Release()
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("Release ") + GetKeyName());
	}
}}}
