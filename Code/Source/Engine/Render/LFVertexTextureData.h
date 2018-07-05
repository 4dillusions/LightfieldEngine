/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Collections\LFDictionary.h"
#include "..\..\Core\Common\LFString.h"

namespace LFCore { namespace Math
{
	class LFVector2D;
}}

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFVertexTextureData
	{ 
	protected:
		LFCore::Common::LFString vertexTextureDataCode;
		static LFCore::Collections::LFDictionary<LFCore::Common::LFString, LFVertexTextureData *> dataList; //TKey: vertexTextureDataCode
		
		static LFCore::Common::LFString GenerateVertexTextureDataCode(const LFCore::Math::LFVector2D &size, const LFCore::Math::LFVector2D &atlasSize);

	public:
		virtual ~LFVertexTextureData() { };

		LFCore::Common::LFString &VertexTextureDataCode() { return vertexTextureDataCode; }
		
		static LFVertexTextureData *Find(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);
		virtual void CreateVertexTextureData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize) = 0; //create a quad (atlasSize = 1, 1) or quad matrix for atlas (atlasSize > 1, 1)
		virtual void Draw() = 0;

		static void ReleaseList();
	};
}}
