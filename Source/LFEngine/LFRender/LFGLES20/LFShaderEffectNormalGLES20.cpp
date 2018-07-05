/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC
#include "..\..\..\ThirdParty\_Win32_\GLEW\glew.h"
#endif

#include "LFShaderEffectNormalGLES20.h"
#include "LFTextureGLES20.h"
#include "..\LFRenderComponentList.h"
#include "..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
#ifdef WINCLASSIC
	LFShaderEffectNormalGLES20::LFShaderEffectNormalGLES20(const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffectGLES20(LFString(LFSystemData::LFShaderEffectNormalGLES20Name), textureName, vertexSize, atlasSize)
	{ }
#endif

#ifdef TIZEN
	LFShaderEffectNormalGLES20::LFShaderEffectNormalGLES20(Evas_Object *glview, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffectGLES20(glview, LFString(LFSystemData::LFShaderEffectNormalGLES20Name), textureName, vertexSize, atlasSize)
	{ }
#endif

	bool LFShaderEffectNormalGLES20::Create()
	{
		if (LFShaderEffectGLES20::Create())
		{
			LFIoc<LFRenderComponentList *>::Get()->Add(GetKeyName(), this);

			LFString specTextureName = textureName;
			specTextureName.Replace(LFString(".png"), LFString("Spec.png"));
			if (LFTextureGLES20 *tData = dynamic_cast<LFTextureGLES20 *>(LFIoc<LFRenderComponentList *>::Get()->GetItem(LFTexture::CreateName(specTextureName))))
			{
				specTexture = tData;
			}
			else
			{
			#ifdef WINCLASSIC
				specTexture = LFMemoryManager::New<LFTextureGLES20>(INFO, specTextureName);
			#endif

			#ifdef TIZEN
				specTexture = LFMemoryManager::New<LFTextureGLES20>(INFO, glview, specTextureName);
			#endif

				specTexture->Create();
			}

			LFString bumpTextureName = textureName;
			bumpTextureName.Replace(LFString(".png"), LFString("Bump.png"));
			if (LFTextureGLES20 *tData = dynamic_cast<LFTextureGLES20 *>(LFIoc<LFRenderComponentList *>::Get()->GetItem(LFTexture::CreateName(bumpTextureName))))
			{
				bumpTexture = tData;
			}
			else
			{
			#ifdef WINCLASSIC
				bumpTexture = LFMemoryManager::New<LFTextureGLES20>(INFO, bumpTextureName);
			#endif

			#ifdef TIZEN
				bumpTexture = LFMemoryManager::New<LFTextureGLES20>(INFO, glview, bumpTextureName);
			#endif

				bumpTexture->Create();
			}

			#ifdef TIZEN
				ELEMENTARY_GLVIEW_USE(glview);
			#endif

			specTextureIndex = dynamic_cast<LFTextureGLES20 *>(specTexture)->GetTextureIndex();
			specTextureID = glGetUniformLocation(programID, "specTex");
			glUniform1i(specTextureID, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, specTextureIndex);

			bumpTextureIndex = dynamic_cast<LFTextureGLES20 *>(bumpTexture)->GetTextureIndex();
			bumpTextureID = glGetUniformLocation(programID, "bumpTex");
			glUniform1i(bumpTextureID, 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, bumpTextureIndex);

			return true;
		}

		return false;
	}

	void LFShaderEffectNormalGLES20::BeginRender()
	{
		LFShaderEffectGLES20::BeginRender();
	}

	void LFShaderEffectNormalGLES20::Draw()
	{
		LFShaderEffectGLES20::Draw();
	}

	void LFShaderEffectNormalGLES20::EndRender()
	{ }

	void LFShaderEffectNormalGLES20::Release()
	{
		LFShaderEffectGLES20::Release();
	}
}}}}
