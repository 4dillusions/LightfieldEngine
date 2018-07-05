/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFShaderEffectNormalD3D9.h"
#include "LFTextureD3D9.h"
#include "..\..\LFRenderComponentList.h"
#include "..\..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	LFShaderEffectNormalD3D9::LFShaderEffectNormalD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffectD3D9(d3d9Device, LFString(LFSystemData::LFShaderEffectNormalD3D9Name), textureName, vertexSize, atlasSize)
	{ }

	bool LFShaderEffectNormalD3D9::Create()
	{
		if (LFShaderEffectD3D9::Create())
		{
			LFIoc<LFRenderComponentList *>::Get()->Add(GetKeyName(), this);

			LFString specTextureName = textureName;
			specTextureName.Replace(LFString(".png"), LFString("Spec.png"));
			if (LFTextureD3D9 *tData = dynamic_cast<LFTextureD3D9 *>(LFIoc<LFRenderComponentList *>::Get()->GetItem(LFTexture::CreateName(specTextureName))))
			{
				specTexture = tData;
			}
			else
			{
				specTexture = LFMemoryManager::New<LFTextureD3D9>(INFO, d3d9Device, specTextureName);
				specTexture->Create();
			}

			LFString bumpTextureName = textureName;
			bumpTextureName.Replace(LFString(".png"), LFString("Bump.png"));
			if (LFTextureD3D9 *tData = dynamic_cast<LFTextureD3D9 *>(LFIoc<LFRenderComponentList *>::Get()->GetItem(LFTexture::CreateName(bumpTextureName))))
			{
				bumpTexture = tData;
			}
			else
			{
				bumpTexture = LFMemoryManager::New<LFTextureD3D9>(INFO, d3d9Device, bumpTextureName);
				bumpTexture->Create();
			}

			specTextureD3d9 = specTexture->GetTexture();
			hSpecTex = effect->GetParameterByName(nullptr, "specTex");
			effect->SetTexture(hSpecTex, specTextureD3d9);

			bumpTextureD3d9 = bumpTexture->GetTexture();
			hBumpTex = effect->GetParameterByName(nullptr, "bumpTex");
			effect->SetTexture(hBumpTex, bumpTextureD3d9);

			return true;
		}

		return false;
	}

	void LFShaderEffectNormalD3D9::BeginRender()
	{
		LFShaderEffectD3D9::BeginRender();
	}

	void LFShaderEffectNormalD3D9::Draw()
	{
		LFShaderEffectD3D9::Draw();
	}

	void LFShaderEffectNormalD3D9::EndRender()
	{
		LFShaderEffectD3D9::EndRender();
	}

	void LFShaderEffectNormalD3D9::Release()
	{
		LFShaderEffectD3D9::Release();
	}
}}}}

#endif
