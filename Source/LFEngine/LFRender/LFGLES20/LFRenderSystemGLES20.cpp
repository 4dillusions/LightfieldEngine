/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC
#include "..\_Win32_\LFRenderWindowWin32.h"
#include "..\..\..\ThirdParty\_Win32_\GLEW\glew.h"
#include "..\..\..\ThirdParty\_Win32_\GLFW\glfw3.h"
#endif

#include "LFRenderSystemGLES20.h"
#include "LFShaderEffectGLES20.h"
#include "LFShaderEffectBasicGLES20.h"
#include "LFShaderEffectNormalGLES20.h"
#include "..\LFRenderComponentList.h"
#include "..\LFVertexTextureData.h"
#include "..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFCore\LFMath\LFRectangle.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFVector3D.h"

#ifdef TIZEN
#include "..\_Tizen_\LFRenderWindowTizen.h"
#endif

using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
	LFRenderSystemGLES20::LFRenderSystemGLES20() 
	{
		LFIoc<LFLogger>::Get().WriteOutput("Create RenderSystem GLES20");
	}

	LFRenderSystemGLES20::~LFRenderSystemGLES20()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release RenderSystem GLES20");
	}

	void LFRenderSystemGLES20::Init()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Initialize RenderSystem GLES20");

		#ifdef WINCLASSIC
		window = dynamic_cast<LFRenderWindowWin32 *>(LFIoc<LFRenderWindow *>::Get())->GetWindow();
		glfwSwapInterval(LFSystemData::LFIsVsync ? GL_TRUE : GL_FALSE);

		glewInit();
		#endif

		#ifdef TIZEN
		glview =  dynamic_cast<LFRenderWindowTizen *>(LFIoc<LFRenderWindow *>::Get())->GetAd()->glview;
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		LFVector3D backgroundColorGL = backgroundColor.ConvertToFloatColorRGB();

		glViewport(0, 0, LFSystemData::GetWindowWidth(), LFSystemData::GetWindowHeight());

		glClearColor(backgroundColorGL.x, backgroundColorGL.y, backgroundColorGL.z, 1.0f);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glDisable(GL_DEPTH_TEST); //Z buffer

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DITHER);

		GLint textSize = 0;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &textSize);
		LFSystemData::SetMaxTextureSize(textSize);
		LFSystemData::SetGPUName((char *)glGetString(GL_VENDOR), (char *)glGetString(GL_RENDERER));
	}

	void LFRenderSystemGLES20::BeginScene()
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void LFRenderSystemGLES20::EndScene()
	{
		#ifdef WIN32
		glfwSwapBuffers(window);
		#endif
	}

	void LFRenderSystemGLES20::OffsetRelativePosition(LFRectangle &posVertexSize)
	{
		float posX = posVertexSize.position.x == 0 ? 0 : (posVertexSize.position.x * LFSystemData::GetWindowWidthRelativeScale() * 2) / LFSystemData::GetWindowWidth();
		posVertexSize.position.x = -1;
		posVertexSize.position.x += posVertexSize.width;
		posVertexSize.position.x += posX;

		float posY = posVertexSize.position.y == 0 ? 0 : (posVertexSize.position.y * LFSystemData::GetWindowHeightRelativeScale() * 2) / LFSystemData::GetWindowHeight();
		posVertexSize.position.y = 1;
		posVertexSize.position.y -= posVertexSize.height;
		posVertexSize.position.y -= posY;
	}

	void LFRenderSystemGLES20::Draw2DObject(int startVertex)
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glDrawArrays(GL_TRIANGLES, startVertex, 6); //type, first item of array, how many vertex count are there
	}

	LFShaderEffect *LFRenderSystemGLES20::CreateShaderEffect(bool isBasic, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		LFShaderEffect *result;

		LFString shaderName = isBasic ? LFString(LFSystemData::LFShaderEffectBasicGLES20Name) : LFString(LFSystemData::LFShaderEffectNormalGLES20Name);
		if (auto shader = LFIoc<LFRenderComponentList *>::Get()->
			GetItem(LFShaderEffect::GenerateKeyName(shaderName, textureName, LFVertexTextureData::GenerateName(vertexSize, atlasSize))))
		{
			result = dynamic_cast<LFShaderEffectGLES20 *>(shader);
		}
		else
		{
			#ifdef WINCLASSIC
			if (isBasic)
				result = LFMemoryManager::New<LFShaderEffectBasicGLES20>(INFO, textureName, vertexSize, atlasSize);
			else
				result = LFMemoryManager::New<LFShaderEffectNormalGLES20>(INFO, textureName, vertexSize, atlasSize);
			#endif
			
			#ifdef TIZEN
			if (isBasic)
				result = LFMemoryManager::New<LFShaderEffectBasicGLES20>(INFO, glview, textureName, vertexSize, atlasSize);
			else
				result = LFMemoryManager::New<LFShaderEffectNormalGLES20>(INFO, glview, textureName, vertexSize, atlasSize);
			#endif

			result->Create();
		}

		return result;
	}
}}}}
