/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\..\LFIRenderSystem.h"
#include "..\..\..\..\ThirdParty\_Win32_\D3D9\d3d9.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	#define LFFVF (D3DFVF_XYZ | D3DFVF_TEX1)

	/**
		@brief
		Render subsystem for GPU drivers on Win32 platform
	*/
	class LFRenderSystemD3D9 final : public LFIRenderSystem
	{
		D3DCOLOR d3dBackgroundColor;
		LPDIRECT3D9 d3d9 = nullptr;
		LPDIRECT3DDEVICE9 d3d9Device = nullptr;

	public:
		LFRenderSystemD3D9(const LFRenderSystemD3D9 &) = delete;
		LFRenderSystemD3D9(LFRenderSystemD3D9 &&) = delete;
		LFRenderSystemD3D9 &operator=(const LFRenderSystemD3D9 &) = delete;
		LFRenderSystemD3D9 &operator=(LFRenderSystemD3D9 &&) = delete;

		LFRenderSystemD3D9();
		~LFRenderSystemD3D9();

		//LFIRenderSystem functions
		void Init() override;
		void BeginScene() override;
		void EndScene() override;
		void OffsetRelativePosition(LFCore::LFMath::LFRectangle &posVertexSize) override;
		void Draw2DObject(int startVertex) override;
		LFShaderEffect *CreateShaderEffect(bool isBasic,
			const LFCore::LFCommon::LFString &textureName, const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize) override;
	};
}}}}

#endif
