/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRenderGL11.h"
#include "LFVertexTextureDataGL11.h"
#include "LFTextureGL11.h"
#include "..\..\..\Core\Math\LFVector3D.h"
#include "..\..\..\Core\Math\LFVector2D.h"
#include "..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\Engine\Common\LFSystemInfo.h"
#include "..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\Core\IO\LFLogger.h"

#ifdef WIN32
#include <GL\gl.h>
#include "..\..\..\..\Source\Depencies\Glfw\SDK\include\GLFW\glfw3.h"
#include "..\_Win32_\LFRenderWindowWin32.h"
#endif

#ifdef TIZEN
#include <Elementary.h>
#include <Elementary_GL_Helpers.h>
#include "..\_Tizen_\LFRenderWindowTizen.h"
#endif

using namespace LFCore::Math;
using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFEngine::Common;

namespace LFEngine { namespace Render { namespace GL11
{
	LFRenderGL11::LFRenderGL11()
	{ }

	LFRenderGL11::~LFRenderGL11()
	{ }

	void LFRenderGL11::CreateInstance()
	{
		if (instance == nullptr)
			instance = LFNew<LFRenderGL11>(AT);
	}

	void LFRenderGL11::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}

	void LFRenderGL11::Init()
	{
		LFLogger::Instance().WriteOutput("Initialize OpenGL11 Render");

		#ifdef WIN32
		window = ((LFRenderWindowWin32 *)LFRenderWindow::Instance())->Window();
		#endif

		#ifdef TIZEN
		glview = ((LFRenderWindowTizen *)LFRenderWindow::Instance())->GlView();
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		LFVector3D backgroundColorGL = backgroundColor.ConvertToFloatColorRGB();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, LFSystemInfo::WindowWidth(), LFSystemInfo::WindowHeight());
		glScalef(1.0f / LFSystemInfo::WindowWidth(), 1.0f / LFSystemInfo::WindowHeight(), 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(backgroundColorGL.x, backgroundColorGL.y, backgroundColorGL.z, 1.0f);
		glShadeModel(GL_FLAT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glDisable(GL_DEPTH_TEST);
		glEnableClientState(GL_VERTEX_ARRAY);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_TEXTURE_2D);	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DITHER);
	}

	void LFRenderGL11::BeginScene()
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glClear(GL_COLOR_BUFFER_BIT);
	}

	void LFRenderGL11::EndScene()
	{
		//glFlush();

		#ifdef WIN32
		glfwSwapBuffers(window);
		#endif
	}

	LFVertexTextureData *LFRenderGL11::CreateVertexTextureData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		if (LFVertexTextureData *result = dynamic_cast<LFVertexTextureDataGL11 *>(LFVertexTextureData::Find(vertexSize, atlasSize)))
			return result;

		LFVertexTextureData *result = LFNew<LFVertexTextureDataGL11>(AT);
		result->CreateVertexTextureData(vertexSize, atlasSize);

		return result;
	}

	LFTexture *LFRenderGL11::CreateTexture(const LFCore::Common::LFString &textureName)
	{
		if (LFTexture *result = dynamic_cast<LFTextureGL11 *>(LFTexture::Find(textureName)))
			return result;

		LFTexture *result = LFNew<LFTextureGL11>(AT);
		result->CreateTexture(textureName);

		return result;
	}

	void LFRenderGL11::OffsetRelativePosition(LFRectangle &posVertexSize)
	{
		static LFVector2D offset;
		offset.x = ((LFSystemInfo::WindowWidth() / 2.0f) - (posVertexSize.width / 2.0f)) * 2;
		offset.y = -((LFSystemInfo::WindowHeight() / 2.0f) - (posVertexSize.height / 2.0f)) * 2;

		posVertexSize.position.x *= 2;
		posVertexSize.position.y *= -2;
		posVertexSize.position -= offset;
	}

	void LFRenderGL11::Draw2DObject(const LFVector2D &position, int startVertex)
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glPushMatrix();
			glTranslatef(position.x, position.y, 0.0f);
			glDrawArrays(GL_TRIANGLES, startVertex, 6);
		glPopMatrix();
	}
}}}
