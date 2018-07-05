/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFTexture.h"

#ifdef WINCLASSIC
#include "..\..\..\..\Source\ThirdParty\_Win32_\GLFW\glfw3.h"
#endif

#ifdef TIZEN
#include <Elementary_GL_Helpers.h>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
	class LFTextureGLES20 final : public LFTexture
	{
#ifdef TIZEN
		Evas_Object *glview;
#endif

		GLuint textureIndex;

	public:
#ifdef WINCLASSIC
		explicit LFTextureGLES20(const LFCore::LFCommon::LFString &textureName);
#endif

#ifdef TIZEN
		LFTextureGLES20(Evas_Object *glview, const LFCore::LFCommon::LFString &textureName);
#endif

		~LFTextureGLES20() = default;

		GLuint GetTextureIndex() const;

		//LFRenderComponent functions
		bool Create() override;
		void BeginRender() override;
		void Draw() override;
		void EndRender() override;
		void Release() override;
	};
}}}}
