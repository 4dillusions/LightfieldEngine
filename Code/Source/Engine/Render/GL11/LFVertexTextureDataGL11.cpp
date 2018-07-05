/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVertexTextureDataGL11.h"
#include "..\..\..\Core\\Math\LFVector2D.h"
#include "..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\Core\IO\LFLogger.h"

#ifdef TIZEN
#include "..\..\LFEngine\src\Render\_Tizen_\LFRenderWindowTizen.h"
#include <Elementary_GL_Helpers.h>
#endif

using namespace LFCore::Math;
using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFVertexTextureDataGL11::LFVertexTextureDataGL11() :
		#ifdef TIZEN
		glview(nullptr),
		#endif

		vertexData(nullptr), textureData(nullptr)
	{ }

	LFVertexTextureDataGL11::~LFVertexTextureDataGL11()
	{ 
		LFDeleteArray(vertexData);
		LFDeleteArray(textureData);
	}

	void LFVertexTextureDataGL11::CreateVertexAtlasData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		#ifdef TIZEN
		if (glview == nullptr)
			glview = ((LFRenderWindowTizen *)LFRenderWindow::Instance())->GlView();
		#endif

		/*                      ____
		1 (-1,  1)   2 (1,  1)  |  /    /|
			                    | /    / |
		3 (-1, -1)   4 (1, -1)  |/    /__|
		*/
		GLfloat vertices[] =
		{
			-vertexSize.x, vertexSize.y, //1
			vertexSize.x, vertexSize.y, //2
			-vertexSize.x, -vertexSize.y, //3

			vertexSize.x, vertexSize.y, //2
			vertexSize.x, -vertexSize.y, //4
			-vertexSize.x, -vertexSize.y, //3
		};

		vertexData = LFNewArray<GLfloat>(AT, (int)atlasSize.x * (int)atlasSize.y * verticesCount);
		for (int quads = 0, index = 0; quads < atlasSize.x * atlasSize.y; ++quads)
			for (int verts = 0; verts < verticesCount; ++verts, ++index)
				vertexData[index] = vertices[verts];
	}

	void LFVertexTextureDataGL11::CreateTextureAtlasData(const LFVector2D &atlasSize)
	{
		/*                      ___
		1 (0, 0)	2 (1, 0)   |  /    /|
		                       | /    / |
		3 (0, 1)	4 (1, 1)   |/    /__|
		*/
		GLfloat coords[] =
		{
			0.0f, 0.0f, //1
			1.0f, 0.0f, //2
			0.0f, 1.0f, //3
			
			1.0f, 0.0f, //2
			1.0f, 1.0f, //4
			0.0f, 1.0f, //3
		};

		textureData = LFNewArray<GLfloat>(AT, (int)atlasSize.x * (int)atlasSize.y * verticesCount);
		float stepX = (1 / atlasSize.x);
		float stepY = (1 / atlasSize.y);

		for (int x = 0, index = 0; x < atlasSize.x; ++x)
			for (int y = 0; y < atlasSize.y; ++y)
				for (int verts = 0; verts < verticesCount; ++verts, ++index)
					if (verts % 2 == 0) textureData[index] = ((coords[verts] + y) * stepY);
					else textureData[index] = ((coords[verts] + x) * stepX);
	}

	void LFVertexTextureDataGL11::CreateVertexTextureData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		if (vertexData == nullptr && textureData == nullptr)
		{
			CreateVertexAtlasData(vertexSize, atlasSize);
			CreateTextureAtlasData(atlasSize);
			vertexTextureDataCode = GenerateVertexTextureDataCode(vertexSize, atlasSize);

			LFString log;
			log += "Create new vertex texture data: ";
			log += vertexTextureDataCode;
			LFLogger::Instance().WriteOutput(log);

			dataList.Add(vertexTextureDataCode, this);
		}
	}

	void LFVertexTextureDataGL11::Draw()
	{
		#ifdef TIZEN
		glview = ((LFRenderWindowTizen *)LFRenderWindow::Instance())->GlView();
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glVertexPointer(2, GL_FLOAT, 0, vertexData);
		glTexCoordPointer(2, GL_FLOAT, 0, textureData);
	}
}}
