/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFTextureD3D9.h"
#include "..\..\..\..\ThirdParty\_Win32_\D3D9\d3dx9.h"
#include "..\..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\LFRenderComponentList.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	LFTextureD3D9::LFTextureD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFString &textureName)
		: LFTexture(textureName), d3d9Device(d3d9Device), texture(nullptr)
	{ }

	LPDIRECT3DTEXTURE9 LFTextureD3D9::GetTexture() const
	{
		return texture;
	}

	bool LFTextureD3D9::Create()
	{
		D3DXIMAGE_INFO imageInfo;

		bool isTextureNull = FAILED(D3DXGetImageInfoFromFile(const_cast<LFString &>(name).ToLpctstr(), &imageInfo)) ||
			FAILED(D3DXCreateTextureFromFileEx(d3d9Device, const_cast<LFString &>(name).ToLpctstr(), imageInfo.Width, imageInfo.Height, 1,
				D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, nullptr, nullptr, &texture));

		if (!CheckTexture(isTextureNull))
			return false;

		textureWidth = imageInfo.Width;
		textureHeight = imageInfo.Height;
		CheckTextureSize();

		LFString log("Create new texture: ");
		log += name;
		LFIoc<LFLogger>::Get().WriteOutput(log);

		LFIoc<LFRenderComponentList *>::Get()->Add(name, this);

		return true;
	}

	void LFTextureD3D9::BeginRender()
	{ }

	void LFTextureD3D9::Draw()
	{ }

	void LFTextureD3D9::EndRender()
	{ }

	void LFTextureD3D9::Release()
	{
		LFTexture::Release();

		if (texture != nullptr)
		{
			texture->Release();
			texture = nullptr;
		}
	}
}}}}

#endif