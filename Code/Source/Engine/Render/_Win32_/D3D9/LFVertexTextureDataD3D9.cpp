/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LFVertexTextureDataD3D9.h"
#include "LFRenderD3D9.h"
#include "..\..\..\..\Core\\Math\LFVector2D.h"
#include "..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\Core\IO\LFLogger.h"

using namespace LFCore::Math;
using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFVertexTextureDataD3D9::LFVertexTextureDataD3D9(LPDIRECT3DDEVICE9 d3d9Device)  : d3d9Device(d3d9Device)
	{ }

	LFVertexTextureDataD3D9::~LFVertexTextureDataD3D9()
	{ }

	void LFVertexTextureDataD3D9::CreateVertexTextureAtlasData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		/*
		vertex
		------                  ____
		1 (-1,  1)   2 (1,  1)  |  /    /|
			                    | /    / |
		3 (-1, -1)   4 (1, -1)  |/    /__|
		
		texture
		-------                  ___
		1 (0, 0)	2 (1, 0)    |  /    /|
		                        | /    / |
		3 (0, 1)	4 (1, 1)    |/    /__|
		*/
		float vertexSizeX = vertexSize.x / 2.0f;
		float vertexSizeY =  vertexSize.y / 2.0f;
		VERTEX_TEXTURE_FORMAT vertices[] =
		{
			{ -vertexSizeX, vertexSizeY, 0.0f, 0.0f, 0.0f }, //1
			{ vertexSizeX, vertexSizeY, 0.0f, 1.0f, 0.0f }, //2
			{ -vertexSizeX, -vertexSizeY, 0.0f, 0.0f, 1.0f }, //3

			{ vertexSizeX, vertexSizeY, 0.0f, 1.0f, 0.0f }, //2
			{ vertexSizeX, -vertexSizeY, 0.0f, 1.0f, 1.0f }, //4
			{ -vertexSizeX, -vertexSizeY, 0.0f, 0.0f, 1.0f }, //3
		};

		d3d9Device->CreateVertexBuffer((int)atlasSize.x * (int)atlasSize.y * verticesCount * sizeof(VERTEX_TEXTURE_FORMAT), 
			D3DUSAGE_WRITEONLY, LFFVF, D3DPOOL_DEFAULT, &vertexTextureData, 0);
		VERTEX_TEXTURE_FORMAT *vertexBuffer;
		vertexTextureData->Lock(0, sizeof(vertices), (VOID **)&vertexBuffer, 0);
		
		float stepX = (1 / atlasSize.x);
		float stepY = (1 / atlasSize.y);
		for (int y = 0, index = 0; y < atlasSize.y; ++y)
			for (int x = 0; x < atlasSize.x; ++x)
				for (int verts = 0; verts < verticesCount; ++verts, ++index)
				{
					vertexBuffer[index].x = vertices[verts].x;
					vertexBuffer[index].y = vertices[verts].y;
					vertexBuffer[index].z = vertices[verts].z;

					vertexBuffer[index].u = ((vertices[verts].u + x) * stepX);
					vertexBuffer[index].v = ((vertices[verts].v + y) * stepY);
				}
		
		vertexTextureData->Unlock();
	}

	void LFVertexTextureDataD3D9::CreateVertexTextureData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		CreateVertexTextureAtlasData(vertexSize, atlasSize);
		vertexTextureDataCode = GenerateVertexTextureDataCode(vertexSize, atlasSize);

		LFString log;
		log += "Create new vertex texture data: ";
		log += vertexTextureDataCode;
		LFLogger::Instance().WriteOutput(log);

		dataList.Add(vertexTextureDataCode, this);
	}

	void LFVertexTextureDataD3D9::Draw()
	{
		d3d9Device->SetStreamSource(0, vertexTextureData, 0, sizeof(VERTEX_TEXTURE_FORMAT));
	}
}}

#endif
