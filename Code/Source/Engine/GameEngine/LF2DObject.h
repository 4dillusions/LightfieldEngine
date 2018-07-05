/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFGameCompositComponent.h"
#include "..\..\Core\\Math\LFVector2D.h"
#include "..\..\Core\\Math\LFRectangle.h"

namespace LFEngine { namespace Render
{
	class LFRender;
	class LFVertexTextureData;
	class LFTexture;
}}

namespace LFEngine { namespace GameEngine
{
	class LFScreen;
	class LFLayer;
	class LFSceneGraph;

	class LFENGINE_LIBRARY LF2DObject : public LFCore::Common::LFGameCompositComponent
	{
	private:
		void GenerateGroupCode();
		void SetAtlasSize(LFCore::Math::LFRectangle &atlasPosSize);

	protected:
		void SetRelativeScale(LFCore::Math::LFRectangle &rectangle);
		void SetStartVertex();
		LFLayer *layer;
		LFSceneGraph *sceneGraph;
		
		LFCore::Common::LFString textureName;
		LFEngine::Render::LFRender *render;
		LFCore::Math::LFRectangle posVertexSize;
		LFCore::Math::LFRectangle atlasPosSize;
		LFEngine::Render::LFVertexTextureData *vertexTextureData;
		LFEngine::Render::LFTexture *texture;
		int startVertex;
		LFCore::Common::LFString groupCode; //vertexTextureData + textureName(this->Name)
		bool isRenderable;

	public:
		LF2DObject(const LFCore::Common::LFString &name, bool isChildrenDestructDelete = true);
		LF2DObject(const LFCore::Common::LFString &name, const LFCore::Common::LFString &textureName, LFCore::Math::LFRectangle &posVertexSize, LFCore::Math::LFRectangle &atlasPosSize);
		virtual ~LF2DObject();

		void PositionAbsolute(const LFCore::Math::LFVector2D &screenPosition); //offset sprite: gui coordinate system -> render coordinate system
		void PositionRelative(const LFCore::Math::LFVector2D &offset); //offset sprite on render coordinate system
		LFCore::Math::LFRectangle PosSize() { return posVertexSize; } //render position and GUI size

		LFEngine::Render::LFVertexTextureData *VertexTextureData() const { return vertexTextureData; }
		LFEngine::Render::LFTexture *Texture() const { return texture; }
		LFCore::Common::LFString &GroupCode() { return groupCode; }

		void Layer(LFLayer *layer); //set layer and scene graph pointers
		bool IsActive(); //this object on active screen or not

		//LFGameCompositComponent
		virtual void Update(double deltaTime);
	};
}}
