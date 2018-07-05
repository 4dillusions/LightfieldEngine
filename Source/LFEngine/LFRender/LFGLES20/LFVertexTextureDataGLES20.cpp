/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVertexTextureDataGLES20.h"
#include "..\LFRenderComponentList.h"
#include "..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
#ifdef TIZEN
	LFVertexTextureDataGLES20::LFVertexTextureDataGLES20(Evas_Object *glview, const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize)
		: LFVertexTextureData(vertexSize, atlasSize), glview(glview)
	{ }
#endif

#ifdef WINCLASSIC
	LFVertexTextureDataGLES20::LFVertexTextureDataGLES20(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFVertexTextureData(vertexSize, atlasSize)
	{ }
#endif

	bool LFVertexTextureDataGLES20::Create()
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		/*                      ____
		0 (-1,  1)   1 (1,  1)  |  /    /|
								| /    / |
		2 (-1, -1)   3 (1, -1)  |/    /__|
		*/
		GLfloat vertices[] =
		{
			-vertexSize.x, vertexSize.y, 0, //0
			vertexSize.x, vertexSize.y, 0, //1
			-vertexSize.x, -vertexSize.y, 0,  //2

			vertexSize.x, vertexSize.y, 0, //1
			vertexSize.x, -vertexSize.y, 0, //3
			-vertexSize.x, -vertexSize.y, 0, //2
		};

		vertexData = LFMemoryManager::NewArray<GLfloat>(INFO, static_cast<int>(atlasSize.x) * static_cast<int>(atlasSize.y) * verticesCount);
		for (int quads = 0, index = 0; quads < atlasSize.x * atlasSize.y; ++quads)
			for (int verts = 0; verts < verticesCount; ++verts, ++index)
				vertexData[index] = vertices[verts];

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(atlasSize.x) * static_cast<int>(atlasSize.y) * sizeof(vertices), vertexData, GL_STATIC_DRAW);

		/*                      ___
		0 (0, 0)	1 (1, 0)   |  /    /|
							   | /    / |
		2 (0, 1)	3 (1, 1)   |/    /__|
		*/
		GLfloat coords[] =
		{
			0.0f, 0.0f, //0
			1.0f, 0.0f, //1
			0.0f, 1.0f, //2

			1.0f, 0.0f, //1
			1.0f, 1.0f, //3
			0.0f, 1.0f, //2
		};

		textureData = LFMemoryManager::NewArray<GLfloat>(INFO, static_cast<int>(atlasSize.x) * static_cast<int>(atlasSize.y) * uvCount);
		float stepX = (1 / atlasSize.x);
		float stepY = (1 / atlasSize.y);

		for (int x = 0, index = 0; x < atlasSize.x; ++x)
			for (int y = 0; y < atlasSize.y; ++y)
				for (int verts = 0; verts < uvCount; ++verts, ++index)
					if (verts % 2 == 0) textureData[index] = ((coords[verts] + y) * stepY);
					else textureData[index] = ((coords[verts] + x) * stepX);

		glGenBuffers(1, &uvBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
		glBufferData(GL_ARRAY_BUFFER, static_cast<int>(atlasSize.x) * static_cast<int>(atlasSize.y) * sizeof(coords), textureData, GL_STATIC_DRAW);

		GenerateName();

		LFString log("Create new vertex texture data: ");
		log += name;
		LFIoc<LFLogger>::Get().WriteOutput(log);

		LFIoc<LFRenderComponentList *>::Get()->Add(name, this);

		return true;
	}

	void LFVertexTextureDataGLES20::BeginRender()
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	}

	void LFVertexTextureDataGLES20::Draw()
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glBindBuffer(GL_ARRAY_BUFFER, uvBufferID);
	}

	void LFVertexTextureDataGLES20::EndRender()
	{ }

	void LFVertexTextureDataGLES20::Release()
	{
		LFVertexTextureData::Release();

		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		if (textureData != nullptr)
		{
#ifdef WINCLASSIC
			glDeleteBuffers(1, &uvBufferID);
#endif
			LFMemoryManager::DeleteArray(textureData);
		}

		if (vertexData != nullptr)
		{
#ifdef WINCLASSIC
			glDeleteBuffers(1, &vertexBufferID);
#endif
			LFMemoryManager::DeleteArray(vertexData);
		}
	}
}}}}
