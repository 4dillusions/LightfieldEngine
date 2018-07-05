/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVertexTextureData.h"
#include "..\LFCore\LFMath\LFVector2D.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFVertexTextureData::LFVertexTextureData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFRenderComponent(LFString("Unnamed")), vertexSize(vertexSize), atlasSize(atlasSize)
	{ }

	LFString LFVertexTextureData::GenerateName(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		if (vertexSize == LFVector2D())
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "vertexSize {0, 0} - LFVertexTextureData::GenerateName");
			return LFString("Wrong size!");
		}

		LFString result(vertexSize.x);
		result += "_";
		result += vertexSize.y;

		if (atlasSize > LFVector2D(1, 1)) //one texture: 1, 1 | atlas (256 tiles): 16, 16
			result += "_atlas";

		return result;
	}

	void LFVertexTextureData::GenerateName()
	{
		name = GenerateName(vertexSize, atlasSize);
	}

	void LFVertexTextureData::Release()
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("Release vertex texture data ") + name);
	}
}}}
