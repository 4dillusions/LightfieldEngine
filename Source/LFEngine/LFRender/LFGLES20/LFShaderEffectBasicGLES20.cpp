/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFShaderEffectBasicGLES20.h"
#include "..\LFRenderComponentList.h"
#include "..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
#ifdef WINCLASSIC
	LFShaderEffectBasicGLES20::LFShaderEffectBasicGLES20(const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffectGLES20(LFString(LFSystemData::LFShaderEffectBasicGLES20Name), textureName, vertexSize, atlasSize)
	{ }
#endif

#ifdef TIZEN
	LFShaderEffectBasicGLES20::LFShaderEffectBasicGLES20(Evas_Object *glview, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffectGLES20(glview, LFString(LFSystemData::LFShaderEffectBasicGLES20Name), textureName, vertexSize, atlasSize)
	{ }
#endif

	bool LFShaderEffectBasicGLES20::Create()
	{
		if (LFShaderEffectGLES20::Create())
		{
			LFIoc<LFRenderComponentList *>::Get()->Add(GetKeyName(), this);
			return true;
		}

		return false;
	}

	void LFShaderEffectBasicGLES20::BeginRender()
	{
		LFShaderEffectGLES20::BeginRender();
	}

	void LFShaderEffectBasicGLES20::Draw()
	{
		LFShaderEffectGLES20::Draw();
	}

	void LFShaderEffectBasicGLES20::EndRender()
	{ }

	void LFShaderEffectBasicGLES20::Release()
	{
		LFShaderEffectGLES20::Release();
	}
}}}}
