/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\..\LFTexture.h"
#include "..\..\..\..\ThirdParty\_Win32_\D3D9\d3d9.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	class LFTextureD3D9 final : public LFTexture
	{
		LPDIRECT3DDEVICE9 d3d9Device;
		LPDIRECT3DTEXTURE9 texture;

	public:
		LFTextureD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFCore::LFCommon::LFString &textureName);
		~LFTextureD3D9() = default;

		LPDIRECT3DTEXTURE9 GetTexture() const;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}

#endif
