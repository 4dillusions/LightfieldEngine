/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFRenderComponent.h"
#include "..\LFCore\LFMath\LFVector2D.h"
#include "..\LFCore\LFMath\LFColor.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFVertexTextureData;
	class LFTexture;

	class LFShaderEffect : public LFRenderComponent
	{
		LFCore::LFCommon::LFString keyName; //name + textureName + vertexTextureDataName

	protected:
		LFCore::LFCommon::LFString textureName;
		LFCore::LFCommon::LFString vertexTextureDataName;
		LFCore::LFMath::LFVector2D vertexSize, atlasSize;
		LFCore::LFMath::LFVector2D relativePosition; //position in GL and D3D system
		LFCore::LFMath::LFColor color; //custom color
		LFVertexTextureData *vertexTextureData = nullptr;
		LFTexture *texture = nullptr;

	public:
		explicit LFShaderEffect(const LFCore::LFCommon::LFString &effectName, const LFCore::LFCommon::LFString &textureName, 
			const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
		virtual ~LFShaderEffect() = default;

		static LFCore::LFCommon::LFString GenerateKeyName(const LFCore::LFCommon::LFString &shaderName, const LFCore::LFCommon::LFString &textureName, 
			const LFCore::LFCommon::LFString &vertexTextureDataName);
		const LFCore::LFCommon::LFString &GetKeyName();

		void SetRelativePosition(const LFCore::LFMath::LFVector2D &relativePosition);
		void SetColor(const LFCore::LFMath::LFColor &color);

		//LFRenderComponent functions
		bool Create() override = 0;
		void BeginRender() override = 0;
		void Draw() override = 0;
		void EndRender() override = 0;
		void Release() override;
	};
}}}
