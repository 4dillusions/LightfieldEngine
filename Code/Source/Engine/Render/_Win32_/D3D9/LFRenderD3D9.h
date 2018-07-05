/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\..\LFRender.h"
#include <d3d9.h>

namespace LFCore { namespace Math
{
	class LFMatrix4;
}}

namespace LFEngine { namespace Render { namespace D3D9
{
	#define LFFVF D3DFVF_XYZ | D3DFVF_TEX1

	class LFENGINE_LIBRARY LFRenderD3D9 : public LFEngine::Render::LFRender
	{ 
	private:
		D3DCOLOR d3dBackgroundColor;
		LPDIRECT3D9 d3d9;
		LPDIRECT3DDEVICE9 d3d9Device;

	public:
		LFRenderD3D9();
		virtual ~LFRenderD3D9();

		static void CreateInstance();
		static void ReleaseInstance();

		//LFRender
		virtual void Init();
		virtual void BeginScene();
		virtual void EndScene();
		virtual LFVertexTextureData *CreateVertexTextureData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);
		virtual LFTexture *CreateTexture(const LFCore::Common::LFString &textureName);
		virtual void OffsetRelativePosition(LFCore::Math::LFRectangle &posVertexSize);
		virtual void Draw2DObject(const LFCore::Math::LFVector2D &position, int startVertex);
	};
}}}

#endif
