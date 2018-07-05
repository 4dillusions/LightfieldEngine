/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\..\LFVertexTextureData.h"
#include <d3d9.h>

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFVertexTextureDataD3D9 : public LFVertexTextureData
	{ 
	private:
		LPDIRECT3DDEVICE9 d3d9Device;
		LPDIRECT3DVERTEXBUFFER9 vertexTextureData;
		static const int verticesCount = 6;

		struct VERTEX_TEXTURE_FORMAT
		{
			float x, y, z; //pos
			float u, v; //text coords
		};

		void CreateVertexTextureAtlasData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);

	public:
		LFVertexTextureDataD3D9(LPDIRECT3DDEVICE9 d3d9Device);
		virtual ~LFVertexTextureDataD3D9();

		virtual void CreateVertexTextureData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);
		virtual void Draw();
	};
}}

#endif
