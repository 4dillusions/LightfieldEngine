/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVertexTextureData.h"
#include "..\..\Core\\Math\LFVector2D.h"
#include "..\..\Core\\IO\LFLogger.h"
#include <assert.h>

using namespace LFCore::Common;
using namespace  LFCore::Math;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFCore::Collections::LFDictionary<LFCore::Common::LFString, LFVertexTextureData *> LFVertexTextureData::dataList(false);

	LFVertexTextureData *LFVertexTextureData::Find(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		return dataList.FindItem(GenerateVertexTextureDataCode(vertexSize, atlasSize));
	}

	LFString LFVertexTextureData::GenerateVertexTextureDataCode(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize)
	{
		if (vertexSize == LFVector2D())
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "vertexSize {0, 0} - LFVertexTextureData::GenerateVertexTextureDataCode");

		LFString result;
		
		result.Append(vertexSize.x);
		result.Append("_");		
		result.Append(vertexSize.y);
		
		if (atlasSize > LFVector2D(1, 1)) 
			result.Append("_atlas");

		return result;
	}

	void LFVertexTextureData::ReleaseList()
	{
		LFLogger::Instance().WriteOutput("Release VertexTextureDataList");
		dataList.DeleteAll();
	}
}}
