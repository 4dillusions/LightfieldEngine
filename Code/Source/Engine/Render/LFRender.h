/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\\Math\LFColor.h"

namespace LFCore { namespace Math
{
	class LFVector2D;
	class LFRectangle;
}}

namespace LFCore { namespace Common
{
	class LFString;
}}

namespace LFEngine { namespace Render
{
	class LFVertexTextureData;
	class LFTexture;

	class LFENGINE_LIBRARY LFRender
	{ 
	protected:
		static LFRender *instance;
		LFCore::Math::LFColor backgroundColor;

	public:
		enum LFRenderType { RT_OpenGL11, RT_Direct3D9 };

		LFRender();
		virtual ~LFRender();

		static LFRender *Instance() { return instance; }

		static LFRenderType RenderType();

		virtual void Init() = 0;
		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;
		virtual LFVertexTextureData *CreateVertexTextureData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize) = 0;
		virtual LFTexture *CreateTexture(const LFCore::Common::LFString &textureName) = 0;
		virtual void OffsetRelativePosition(LFCore::Math::LFRectangle &posVertexSize) = 0;
		virtual void Draw2DObject(const LFCore::Math::LFVector2D &position, int startVertex) = 0;
	};
}}
