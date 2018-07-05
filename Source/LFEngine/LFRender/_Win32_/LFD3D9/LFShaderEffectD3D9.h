/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\..\LFShaderEffect.h"
#include "..\..\..\..\ThirdParty\_Win32_\D3D9\d3d9.h"
#include "..\..\..\..\ThirdParty\_Win32_\D3D9\d3dx9.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	class LFShaderEffectD3D9 : public LFShaderEffect
	{
	protected:
		LPDIRECT3DDEVICE9 d3d9Device;
		ID3DXEffect *effect = nullptr;
		D3DXHANDLE technique = nullptr;
		D3DXHANDLE gWorldViewProjection = nullptr;
		D3DXHANDLE hTexture = nullptr;
		D3DXHANDLE hColor = nullptr;
		D3DXVECTOR4 d3dColor;
		LPDIRECT3DTEXTURE9 textureD3D9 = nullptr;
		D3DXMATRIX projection;

	public:
		LFShaderEffectD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFCore::LFCommon::LFString &effectName, const LFCore::LFCommon::LFString &textureName, 
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
		virtual ~LFShaderEffectD3D9() = default;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}

#endif
