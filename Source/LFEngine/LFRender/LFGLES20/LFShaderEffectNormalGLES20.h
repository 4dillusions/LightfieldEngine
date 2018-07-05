/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFShaderEffectGLES20.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
	class LFTextureGLES20;

	class LFShaderEffectNormalGLES20 final : public LFShaderEffectGLES20
	{
		GLuint specTextureID = 0;
		GLuint bumpTextureID = 0;
		GLuint specTextureIndex = 0;
		GLuint bumpTextureIndex = 0;
		LFTextureGLES20 *specTexture = nullptr;
		LFTextureGLES20 *bumpTexture = nullptr;

	public:
#ifdef WINCLASSIC
		LFShaderEffectNormalGLES20(const LFCore::LFCommon::LFString &textureName,
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
#endif

#ifdef TIZEN
		LFShaderEffectNormalGLES20(Evas_Object *glview, const LFCore::LFCommon::LFString &textureName,
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
#endif

		~LFShaderEffectNormalGLES20() = default;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}
