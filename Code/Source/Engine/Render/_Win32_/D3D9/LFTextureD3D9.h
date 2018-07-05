/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\..\LFTexture.h"
#include <d3d9.h>

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFTextureD3D9 : public LFTexture
	{ 
	private:
		LPDIRECT3DDEVICE9 d3d9Device;
		LPDIRECT3DTEXTURE9 texture;
		
	public:
		LFTextureD3D9(LPDIRECT3DDEVICE9 d3d9Device);
		virtual ~LFTextureD3D9();

		virtual void CreateTexture(const LFCore::Common::LFString &textureName);
		virtual void Draw();
	};
}}

#endif
