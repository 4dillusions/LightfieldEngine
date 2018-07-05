/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFGameCompositeComponent.h"
#include "..\LFCore\LFMath\LFRectangle.h"
#include "..\LFCore\LFMath\LFColor.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFIRenderSystem;
	class LFShaderEffect;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	class LFScreen;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFControl : public LFCore::LFCommon::LFGameCompositeComponent
	{
	protected:
		LFRender::LFIRenderSystem *render = nullptr;
		LFRender::LFShaderEffect *shader = nullptr;
		LFScene::LFScreen *screen = nullptr;
		LFCore::LFMath::LFRectangle posVertexSize;
		LFCore::LFMath::LFRectangle posAtlasSize;
		bool isRenderable = true;
		int startVertex = 0;
		LFCore::LFMath::LFVector2D position;
		LFCore::LFMath::LFColor color;

		void SetStartVertex();
		void SetRelativeScale(const LFCore::LFMath::LFRectangle &rectangle);
		void SetAtlasSize(const LFCore::LFMath::LFRectangle &atlasPosSize);

	public:
		LFControl(const LFCore::LFCommon::LFString &name, const LFCore::LFCommon::LFString &textureName, const LFCore::LFMath::LFRectangle &posVertexSize, const LFCore::LFMath::LFRectangle &posAtlasSize, const LFCore::LFMath::LFColor &color, bool isBasicShader);
		virtual ~LFControl();

		bool GetIsRenderable() const;
		LFRender::LFShaderEffect *GetShader() const;
		virtual void SetPosition(const LFCore::LFMath::LFVector2D &position);
		const LFCore::LFMath::LFVector2D &GetPosition() const;
		virtual void SetColor(const LFCore::LFMath::LFColor &color);
		void SetScreen(LFScene::LFScreen *screen);

		//LFGameCompositeComponent functions
		void Add(LFGameComponent *control) override;
		void Remove(LFGameComponent *control) override;
		void Update(double deltaTime) override;
	};
}}}
