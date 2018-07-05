/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTexture.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFMath\LFMath.h"
#include "..\LFCore\LFCommon\LFVFSManager.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFTexture::LFTexture(const LFString &textureName) 
		: LFRenderComponent(textureName)
	{
		name = CreateName(name);
	}

	int LFTexture::GetTextureWidth() const
	{
		return textureWidth;
	}

	int LFTexture::GetTextureHeight() const
	{
		return textureHeight;
	}

	bool LFTexture::CheckTexture(bool isTextureNull) const
	{
		if (isTextureNull)
		{
			LFString log("Couldn't load texture: ");
			log += name;
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);

			return false;
		}

		return true;
	}

	bool LFTexture::CheckTextureSize() const
	{
		if (!LFMath::IsPowerOfTwo(textureWidth) || !LFMath::IsPowerOfTwo(textureHeight))
		{
			LFString log("Texture size isn't power of two: ");
			log += name;
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Warning, log);

			return false;
		}

		return true;
	}

	LFString LFTexture::CreateName(const LFString &textureName)
	{
		LFString textureFullName(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::Image));
		textureFullName += textureName;
			
		return textureFullName;
	}

	void LFTexture::Release()
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("Release texture ") + name);
	}
}}}
