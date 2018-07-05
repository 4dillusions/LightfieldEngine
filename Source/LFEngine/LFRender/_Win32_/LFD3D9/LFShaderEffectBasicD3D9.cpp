/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFShaderEffectBasicD3D9.h"
#include "..\..\LFRenderComponentList.h"
#include "..\..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	LFShaderEffectBasicD3D9::LFShaderEffectBasicD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffectD3D9(d3d9Device, LFString(LFSystemData::LFShaderEffectBasicD3D9Name), textureName, vertexSize, atlasSize)
	{ }

	bool LFShaderEffectBasicD3D9::Create()
	{
		if (LFShaderEffectD3D9::Create())
		{
			LFIoc<LFRenderComponentList *>::Get()->Add(GetKeyName(), this);
			return true;
		}

		return false;
	}

	void LFShaderEffectBasicD3D9::BeginRender()
	{
		LFShaderEffectD3D9::BeginRender();
	}

	void LFShaderEffectBasicD3D9::Draw()
	{
		LFShaderEffectD3D9::Draw();
	}

	void LFShaderEffectBasicD3D9::EndRender()
	{
		LFShaderEffectD3D9::EndRender();
	}

	void LFShaderEffectBasicD3D9::Release()
	{
		LFShaderEffectD3D9::Release();
	}
}}}}

#endif
