/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFRenderComponent.h"
#include "..\LFCore\LFMath\LFVector2D.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFVertexTextureData : public LFRenderComponent
	{
	protected:
		LFCore::LFMath::LFVector2D vertexSize, atlasSize;

		void GenerateName();

	public:
		LFVertexTextureData(const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);
		virtual ~LFVertexTextureData() = default;

		static LFCore::LFCommon::LFString GenerateName(const LFCore::LFMath::LFVector2D &vertexSize, const LFCore::LFMath::LFVector2D &atlasSize);

		//LFRenderComponent functions
		bool Create() override = 0;
		void BeginRender() override = 0;
		void Draw() override = 0;
		void EndRender() override = 0;
		void Release() override;
	};
}}}
