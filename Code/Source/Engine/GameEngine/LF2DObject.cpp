/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LF2DObject.h"
#include "..\Render\LFVertexTextureData.h"
#include "..\Render\LFRender.h"
#include "..\Render\LFTexture.h"
#include "..\Common\LFSystemInfo.h"
#include "..\..\Core\Common\LFVFSManager.h"
#include "LFLayer.h"
#include "LFSceneGraph.h"
#include <assert.h>

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFEngine::Render;
using namespace LFEngine::Common;

namespace LFEngine { namespace GameEngine
{
	LF2DObject::LF2DObject(const LFString &name, bool isChildrenDestructDelete) : LFGameCompositComponent(name, isChildrenDestructDelete),
		layer(nullptr), sceneGraph(nullptr), render(nullptr), vertexTextureData(nullptr), texture(nullptr), isRenderable(false)
	{ }

	LF2DObject::LF2DObject(const LFString &name, const LFString &textureName, LFRectangle &posVertexSize, LFRectangle &atlasPosSize) : LFGameCompositComponent(name), 
		layer(nullptr), sceneGraph(nullptr), textureName(textureName), render(nullptr), vertexTextureData(nullptr), texture(nullptr), isRenderable(true)
    { 
		render = LFRender::Instance();

		SetRelativeScale(posVertexSize);
		render->OffsetRelativePosition(posVertexSize);
		this->posVertexSize = posVertexSize;
		SetAtlasSize(atlasPosSize);
		SetStartVertex();

		LFString textureFullName;
		textureFullName.Append(LFVFSManager::Instance()->Path(LFVFSManager::CP_IMAGE));
		textureFullName.Append(textureName);

		vertexTextureData = LFRender::Instance()->CreateVertexTextureData(posVertexSize.Size(), this->atlasPosSize.Size());
		texture = LFRender::Instance()->CreateTexture(textureFullName);

		GenerateGroupCode();
	}

	LF2DObject::~LF2DObject()
    { }

	void LF2DObject::PositionAbsolute(const LFVector2D &guiPosition)
	{
		posVertexSize.position = guiPosition;
		render->OffsetRelativePosition(posVertexSize);
	}

	void LF2DObject::PositionRelative(const LFVector2D &offset)
	{
		posVertexSize.position += offset;
	}

	void LF2DObject::Layer(LFLayer *layer)
	{ 
		this->layer = layer;
		sceneGraph = LFSceneGraph::Instance();
	}

	bool LF2DObject::IsActive()
	{
		return sceneGraph->ActiveScreen() == layer->Screen();
	}

	void LF2DObject::GenerateGroupCode()
	{
		assert(vertexTextureData != nullptr);

		groupCode.Append(vertexTextureData->VertexTextureDataCode());
		groupCode.Append("_");
		groupCode.Append(textureName);
	}

	void LF2DObject::SetRelativeScale(LFRectangle &rectangle)
	{
		rectangle.width *= LFSystemInfo::WindowWidthRelativeScale();
		rectangle.height *= LFSystemInfo::WindowHeightRelativeScale();
		rectangle.position.x *= LFSystemInfo::WindowWidthRelativeScale();
		rectangle.position.y *= LFSystemInfo::WindowHeightRelativeScale();

		this->posVertexSize = posVertexSize;
	}

	void LF2DObject::SetAtlasSize(LFRectangle &atlasPosSize)
	{
		this->atlasPosSize = atlasPosSize;
		if (this->atlasPosSize.height <= 0 || this->atlasPosSize.width <= 0)
		{
			this->atlasPosSize.height = 1;
			this->atlasPosSize.width = 1;
		}
	}

	void LF2DObject::SetStartVertex()
	{
		startVertex = ((atlasPosSize.width * atlasPosSize.position.y) + atlasPosSize.position.x) * 6;
	}

	void LF2DObject::Update(double deltaTime)
	{
		if (isRenderable && isVisible)
			render->Draw2DObject(posVertexSize.position, startVertex);
	}
}}
