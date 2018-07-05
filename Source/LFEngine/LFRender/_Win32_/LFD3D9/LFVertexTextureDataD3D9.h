/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\..\LFVertexTextureData.h"
#include "..\..\..\..\ThirdParty\_Win32_\D3D9\d3d9.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	class LFVertexTextureDataD3D9 final : public LFVertexTextureData
	{
		LPDIRECT3DDEVICE9 d3d9Device;
		LPDIRECT3DVERTEXBUFFER9 vertexTextureData;
		static const int verticesCount = 6;

		struct VERTEX_TEXTURE_FORMAT
		{
			float x, y, z; //pos
			float u, v; //text coords
		};

	public:
		LFVertexTextureDataD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
		~LFVertexTextureDataD3D9() = default;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}

#endif
