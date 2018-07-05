/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LFTextureD3D9.h"
#include "..\..\..\..\..\Source\Depencies\D3D9\Include\d3dx9.h"
#include "..\..\..\..\Core\IO\LFLogger.h"
#include "..\..\..\..\Core\Common\LFString.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFTextureD3D9::LFTextureD3D9(LPDIRECT3DDEVICE9 d3d9Device) : d3d9Device(d3d9Device)
	{ }

	LFTextureD3D9::~LFTextureD3D9()
	{ }

	void LFTextureD3D9::CreateTexture(const LFCore::Common::LFString &textureName)
	{		
		D3DXIMAGE_INFO imageInfo;
		
		bool isTextureNull = FAILED(D3DXGetImageInfoFromFile(const_cast<LFString &>(textureName).ToLpctstr(), &imageInfo)) || 
				FAILED(D3DXCreateTextureFromFileEx(d3d9Device, const_cast<LFString &>(textureName).ToLpctstr(), imageInfo.Width, imageInfo.Height, 1, 
				D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, 0, 0, &texture));
		
		if (!CheckTexture(isTextureNull))
			return;

		textureWidth = imageInfo.Width;
		textureHeight = imageInfo.Height;
		CheckTextureSize();

		LFString log;
		log += "Create new texture: ";
		log += textureName;
		LFLogger::Instance().WriteOutput(log);

		dataList.Add(textureName, this);
	}
	
	void LFTextureD3D9::Draw()
	{
		d3d9Device->SetTexture(0, texture);
	}
}}

#endif
