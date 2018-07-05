/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTexture.h"
#include <assert.h>
#include "..\..\Core\\Math\LFMath.h"
#include "..\..\Core\\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFCore::Collections::LFDictionary<LFCore::Common::LFString, LFTexture *> LFTexture::dataList(false);

	bool LFTexture::CheckTexture(bool isTextureNull)
	{
		if (isTextureNull)
		{
			LFString log;
			log.Append("Couldn't load texture: ");
			log.Append(textureName);
			LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, log);

			return false;
		}

		return true;
	}

	bool LFTexture::CheckTextureSize()
	{
		if (!LFMath::IsPowerOfTwo(textureWidth) || !LFMath::IsPowerOfTwo(textureHeight))
		{
			LFString log;
			log.Append("Texture size isn't power of two: ");
			log.Append(textureName);
			LFLogger::Instance().WriteOutput(LFLogger::MT_WARNING, log);

			return false;
		}

		return true;
	}

	LFTexture *LFTexture::Find(const LFCore::Common::LFString &textureName)
	{
		return dataList.FindItem(textureName);
	}

	void LFTexture::ReleaseList()
	{
		LFLogger::Instance().WriteOutput("Release TextureList");
		dataList.DeleteAll();
	}
}}
