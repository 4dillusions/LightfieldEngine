/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTextureGLES20.h"
#include "..\..\..\ThirdParty\SOIL2\SOIL2.h"
#include "..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFRenderComponentList.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
#ifdef WINCLASSIC
	LFTextureGLES20::LFTextureGLES20(const LFCore::LFCommon::LFString &textureName)
		: LFTexture(textureName), textureIndex(0)
	{ }
#endif

#ifdef TIZEN
	LFTextureGLES20::LFTextureGLES20(Evas_Object *glview, const LFCore::LFCommon::LFString & textureName)
		: LFTexture(textureName), glview(glview), textureIndex(0)
	{ }
#endif

	GLuint LFTextureGLES20::GetTextureIndex() const
	{
		return textureIndex;
	}

	bool LFTextureGLES20::Create()
	{
		textureIndex = SOIL_load_OGL_texture(name.ToChar(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO);

		if (textureIndex == 0)
		{
			LFString log("Couldn't load texture: ");
			log += SOIL_last_result();
			LFIoc<LFLogger>::Get().WriteOutput(log);
			
			return false;
		}

		LFString log("Create new texture: ");
		log += name;
		LFIoc<LFLogger>::Get().WriteOutput(log);

		LFIoc<LFRenderComponentList *>::Get()->Add(name, this);

		return true;
	}

	void LFTextureGLES20::BeginRender()
	{ }

	void LFTextureGLES20::Draw()
	{ }

	void LFTextureGLES20::EndRender()
	{ }

	void LFTextureGLES20::Release()
	{
		LFTexture::Release();

#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
#endif

#ifdef WINCLASSIC
		if (glIsTexture(textureIndex))
			glDeleteTextures(1, &textureIndex);
#endif
	}
}}}}
