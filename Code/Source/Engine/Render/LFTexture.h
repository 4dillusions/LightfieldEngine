/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Collections\LFDictionary.h"
#include "..\..\Core\Common\LFString.h"

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFTexture
	{ 
	protected:
		LFCore::Common::LFString textureName;
		int textureWidth, textureHeight;

		static LFCore::Collections::LFDictionary<LFCore::Common::LFString, LFTexture *> dataList; //TKey: textureName
		bool CheckTexture(bool isTextureNull);
		bool CheckTextureSize();

	public:
		virtual ~LFTexture() { };

		LFCore::Common::LFString &TextureName() { return textureName; }
		int TextureWidth() { return textureWidth; }
		int TextureHeight() { return textureHeight; }

		static LFTexture *Find(const LFCore::Common::LFString &textureName);
		virtual void CreateTexture(const LFCore::Common::LFString &textureName) = 0;
		virtual void Draw() = 0;

		static void ReleaseList();
	};
}}
