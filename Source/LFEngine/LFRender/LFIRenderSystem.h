/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFMath\LFColor.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFVector2D;
	class LFRectangle;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFString;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFVertexTextureData;
	class LFTexture;
	class LFShaderEffect;

	/**
		@brief
		Render subsystem for GPU drivers
	*/
	class LFIRenderSystem
	{
	protected:
		LFCore::LFMath::LFColor backgroundColor = LFCore::LFMath::LFColor(51, 51, 51);

	public:
		LFIRenderSystem(const LFIRenderSystem &) = delete;
		LFIRenderSystem(LFIRenderSystem &&) = delete;
		LFIRenderSystem &operator=(const LFIRenderSystem &) = delete;
		LFIRenderSystem &operator=(LFIRenderSystem &&) = delete;

		LFIRenderSystem() = default;
		virtual ~LFIRenderSystem() = default;

		virtual void Init() = 0;
		virtual void BeginScene() = 0;
		virtual void EndScene() = 0;
		virtual void OffsetRelativePosition(LFCore::LFMath::LFRectangle &posVertexSize) = 0;
		virtual void Draw2DObject(int startVertex) = 0;
		virtual LFShaderEffect *CreateShaderEffect(bool isBasic, 
			const LFCore::LFCommon::LFString &textureName, const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize) = 0;
	};
}}}
