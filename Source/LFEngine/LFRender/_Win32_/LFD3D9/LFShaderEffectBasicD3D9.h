/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "LFShaderEffectD3D9.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	class LFShaderEffectBasicD3D9 final : public LFShaderEffectD3D9
	{
	public:
		LFShaderEffectBasicD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFCore::LFCommon::LFString &textureName,
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
		~LFShaderEffectBasicD3D9() = default;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}

#endif
