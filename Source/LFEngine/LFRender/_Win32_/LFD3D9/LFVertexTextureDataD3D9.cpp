/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFVertexTextureDataD3D9.h"
#include "LFRenderSystemD3D9.h"
#include "..\..\LFRenderComponentList.h"
#include "..\..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\..\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	LFVertexTextureDataD3D9::LFVertexTextureDataD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFVertexTextureData(vertexSize, atlasSize), d3d9Device(d3d9Device), vertexTextureData(nullptr)
	{ }

	bool LFVertexTextureDataD3D9::Create()
	{
		float vertexSizeX = vertexSize.x;
		float vertexSizeY = vertexSize.y;
		VERTEX_TEXTURE_FORMAT vertices[] =
		{
			/*
			vertex
			------                  ____
			1 (-1,  1)   2 (1,  1)  |  /    /|
									| /    / |
			3 (-1, -1)   4 (1, -1)  |/    /__|

			texture
			-------                  ___
			0 (0, 0)	1 (1, 0)    |  /    /|
									| /    / |
			2 (0, 1)	3 (1, 1)    |/    /__|
			*/

			{ -vertexSizeX, vertexSizeY, 0.0f, 0.0f, 0.0f }, //0
			{ vertexSizeX, vertexSizeY, 0.0f, 1.0f, 0.0f }, //1
			{ -vertexSizeX, -vertexSizeY, 0.0f, 0.0f, 1.0f }, //2

			{ vertexSizeX, vertexSizeY, 0.0f, 1.0f, 0.0f }, //1
			{ vertexSizeX, -vertexSizeY, 0.0f, 1.0f, 1.0f }, //3
			{ -vertexSizeX, -vertexSizeY, 0.0f, 0.0f, 1.0f }, //2
		};

		d3d9Device->CreateVertexBuffer(static_cast<int>(atlasSize.x) * static_cast<int>(atlasSize.y) * verticesCount * sizeof(VERTEX_TEXTURE_FORMAT),
			D3DUSAGE_WRITEONLY, LFFVF, D3DPOOL_DEFAULT, &vertexTextureData, nullptr);
		VERTEX_TEXTURE_FORMAT *vertexBuffer;
		vertexTextureData->Lock(0, sizeof(vertices), reinterpret_cast<VOID **>(&vertexBuffer), 0);

		float stepX = (1 / atlasSize.x);
		float stepY = (1 / atlasSize.y);
		for (int y = 0, index = 0; y < atlasSize.y; ++y)
			for (int x = 0; x < atlasSize.x; ++x)
				for (int verts = 0; verts < verticesCount; ++verts, ++index)
				{
					vertexBuffer[index].x = vertices[verts].x;
					vertexBuffer[index].y = vertices[verts].y;
					vertexBuffer[index].z = vertices[verts].z;

					vertexBuffer[index].u = (vertices[verts].u + x) * stepX;
					vertexBuffer[index].v = (vertices[verts].v + y) * stepY;
				}

		vertexTextureData->Unlock();

		GenerateName();

		LFString log("Create new vertex texture data: ");
		log += name;
		LFIoc<LFLogger>::Get().WriteOutput(log);

		LFIoc<LFRenderComponentList *>::Get()->Add(name, this);

		return true;
	}

	void LFVertexTextureDataD3D9::BeginRender()
	{
		d3d9Device->SetStreamSource(0, vertexTextureData, 0, sizeof(VERTEX_TEXTURE_FORMAT));
	}

	void LFVertexTextureDataD3D9::Draw()
	{ }

	void LFVertexTextureDataD3D9::EndRender()
	{ }

	void LFVertexTextureDataD3D9::Release()
	{
		LFVertexTextureData::Release();

		if (vertexTextureData != nullptr)
		{
			vertexTextureData->Release();
			vertexTextureData = nullptr;
		}
	}
}}}}

#endif
