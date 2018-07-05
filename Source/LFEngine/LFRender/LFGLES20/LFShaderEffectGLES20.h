/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFShaderEffect.h"
#include "..\..\LFCore\LFMath\LFMatrix4.h"

#ifdef WINCLASSIC
#include "..\..\..\..\Source\ThirdParty\_Win32_\GLFW\glfw3.h"
typedef void Evas_Object;
#endif

#ifdef TIZEN
#include <Elementary_GL_Helpers.h>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
	class LFShaderEffectGLES20 : public LFShaderEffect
	{
#ifdef TIZEN
	protected: Evas_Object *glview;
#endif

	protected:
		GLuint programID = 0;
		GLuint posID = 0;
		GLuint uvID = 0;
		GLuint textureID = 0;
		GLuint textureIndex = 0;
		GLuint worldID = 0;
		GLuint colorID = 0; //custom color
		GLfloat glColor[4];
		LFCore::LFMath::LFMatrix4 gWorldViewProjection;

		GLuint LoadShaders(const LFCore::LFCommon::LFString &vertexFilePath, const LFCore::LFCommon::LFString &fragmentFilePath, Evas_Object *glview = nullptr);

	public:
#ifdef WINCLASSIC
		explicit LFShaderEffectGLES20(const LFCore::LFCommon::LFString &effectName, const LFCore::LFCommon::LFString &textureName,
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
#endif

#ifdef TIZEN
		LFShaderEffectGLES20(Evas_Object *glview, const LFCore::LFCommon::LFString &effectName, const LFCore::LFCommon::LFString &textureName,
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
#endif

		virtual ~LFShaderEffectGLES20() = default;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}
