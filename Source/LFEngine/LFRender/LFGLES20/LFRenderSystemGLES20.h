/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFIRenderSystem.h"

#ifdef WIN32
struct GLFWwindow;
#endif

#ifdef TIZEN
#include <Elementary.h>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
	/**
		@brief
		Render subsystem for GPU drivers on Win32 and Tizen platforms
	*/
	class LFRenderSystemGLES20 final : public LFIRenderSystem
	{
		#ifdef WIN32
		GLFWwindow *window = nullptr;
		#endif

		#ifdef TIZEN
		Evas_Object *glview = nullptr;
		#endif

	public:
		LFRenderSystemGLES20(const LFRenderSystemGLES20 &) = delete;
		LFRenderSystemGLES20(LFRenderSystemGLES20 &&) = delete;
		LFRenderSystemGLES20 &operator=(const LFRenderSystemGLES20 &) = delete;
		LFRenderSystemGLES20 &operator=(LFRenderSystemGLES20 &&) = delete;

		LFRenderSystemGLES20();
		~LFRenderSystemGLES20();

		//LFRenderSystem functions
		void Init() override;
		void BeginScene() override;
		void EndScene() override;
		void OffsetRelativePosition(LFCore::LFMath::LFRectangle &posVertexSize) override;
		void Draw2DObject(int startVertex) override;
		LFShaderEffect *CreateShaderEffect(bool isBasic,
			const LFCore::LFCommon::LFString &textureName, const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize) override;
	};
}}}}
