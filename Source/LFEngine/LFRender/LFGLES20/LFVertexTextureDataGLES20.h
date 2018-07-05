/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#ifdef WINCLASSIC
#include "..\..\..\ThirdParty\_Win32_\GLEW\glew.h"
#endif

#include "..\LFVertexTextureData.h"

#ifdef TIZEN
#include <Elementary_GL_Helpers.h>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
	class LFVertexTextureDataGLES20 final : public LFVertexTextureData
	{
#ifdef TIZEN
		Evas_Object *glview;
#endif

		static const int verticesCount = 18;
		static const int uvCount = 12;

		GLuint vertexBufferID = 0;
		GLfloat *vertexData = nullptr;
		GLuint uvBufferID = 0;
		GLfloat *textureData = nullptr;

	public:
#ifdef TIZEN
		LFVertexTextureDataGLES20(Evas_Object *glview, const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize); //create a quad (atlasSize = 1, 1) or quad matrix for atlas (atlasSize > 1, 1)
#endif

#ifdef WINCLASSIC
		LFVertexTextureDataGLES20(const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize); //create a quad (atlasSize = 1, 1) or quad matrix for atlas (atlasSize > 1, 1)
#endif
		~LFVertexTextureDataGLES20() = default;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}