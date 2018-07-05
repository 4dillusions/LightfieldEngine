/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFGameCompositComponent.h"

namespace LFEngine { namespace Render
{
	class LFVertexTextureData;
	class LFTexture;
}}

namespace LFEngine { namespace GameEngine
{
	class LFENGINE_LIBRARY LF2DObjectGroup : public LFCore::Common::LFGameCompositComponent
	{
	private:
		LFEngine::Render::LFVertexTextureData *vertexTextureData;
		LFEngine::Render::LFTexture *texture;

	public:
		LF2DObjectGroup(const LFCore::Common::LFString &groupCode);
		virtual ~LF2DObjectGroup();

		//LFGameCompositComponent
		void Add(LFGameComponent *lF2DObject);
		void Remove(LFGameComponent *lF2DObject);

		//LFGameComponent
		virtual void Update(double deltaTime);
	};
}}
