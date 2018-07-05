/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFControl.h"
#include "..\LFRender\LFShaderEffect.h"
#include "..\LFCore\LFCommon\LFSystemData.h"
#include "..\LFRender\LFIRenderSystem.h"
#include "..\..\LFEngine\LFScene\LFScreen.h"
#include "..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFGUI;
using namespace LF3Engine::LFEngine::LFRender;
using namespace LF3Engine::LFEngine::LFScene;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFControl::LFControl(const LFString &name, const LFString &textureName, const LFRectangle &posVertexSize, const LFRectangle &posAtlasSize, const LFColor &color, bool isBasicShader)
		: LFGameCompositeComponent(name), posVertexSize(posVertexSize), posAtlasSize(posAtlasSize), position(posVertexSize.position), color(color)
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("create LFControl: ") + name);

		if (!textureName.IsEmpty())
		{
			render = LFIoc<LFIRenderSystem *>::Get();

			SetRelativeScale(posVertexSize);
			render->OffsetRelativePosition(this->posVertexSize);

			SetAtlasSize(posAtlasSize);
			
			SetStartVertex();

			shader = render->
				CreateShaderEffect(isBasicShader, textureName, LFVector2D(this->posVertexSize.width, this->posVertexSize.height), 
					LFVector2D(this->posAtlasSize.width, this->posAtlasSize.height));
		}
		else
			isRenderable = false;
	}

	LFControl::~LFControl()
	{
		LFIoc<LFLogger>::Get().WriteOutput(LFString("release LFControl: ") + name);
	}

	bool LFControl::GetIsRenderable() const
	{
		return isRenderable;
	}

	LFShaderEffect *LFControl::GetShader() const
	{
		return shader;
	}

	//calculate relative position (posVertexSize position) from position and offset children. Relative pos will be updated in LFControl::Update method.
	void LFControl::SetPosition(const LFVector2D &position)
	{
		posVertexSize.SetPosition(position);
		render->OffsetRelativePosition(this->posVertexSize);
		shader->SetRelativePosition(posVertexSize.GetPosition());

		LFVector2D currentPos = this->position;
		LFVector2D posOffset;
		posOffset.x = position.x - currentPos.x;
		posOffset.y = position.y - currentPos.y;

		this->position = position;
		
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (LFControl *control = dynamic_cast<LFControl *>(componentList.Current()))
				control->SetPosition(control->position + posOffset);
	}

	LFVector2D const &LFControl::GetPosition() const
	{
		return position;
	}

	void LFControl::SetColor(const LFColor &color)
	{
		this->color = color;
	}

	void LFControl::SetScreen(LFScreen *screen)
	{
		if (this->screen == nullptr)
			this->screen = screen;
	}
	
	void LFControl::Add(LFGameComponent *control)
	{
		LFControl *result = dynamic_cast<LFControl *>(control);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFControl::Add");
			return;
		}

		LFGameCompositeComponent::Add(result);
	}

	void LFControl::Remove(LFGameComponent *control)
	{
		LFControl *result = dynamic_cast<LFControl *>(control);

		if (result == nullptr)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "nullptr LFControl::Remove");
			return;
		}

		LFGameCompositeComponent::Remove(result);
	}

	void LFControl::Update(double deltaTime)
	{
		if (isRenderable && isVisible && startVertex >= 0)
		{
			shader->SetRelativePosition(posVertexSize.GetPosition());
			shader->SetColor(color);
			shader->Draw();

			render->Draw2DObject(startVertex);
		}

		LFGameCompositeComponent::Update(deltaTime);
	}

	void LFControl::SetStartVertex()
	{
		startVertex = ((posAtlasSize.width * posAtlasSize.position.y) + posAtlasSize.position.x) * 6;
	}

	void LFControl::SetRelativeScale(const LFRectangle &rectangle)
	{
		this->posVertexSize.width = rectangle.width / LFSystemData::LFDefaultWindowWidth;
		this->posVertexSize.height = rectangle.height / LFSystemData::LFDefaultWindowHeight;
	}

	void LFControl::SetAtlasSize(const LFRectangle &atlasPosSize)
	{
		this->posAtlasSize = atlasPosSize;
		if (this->posAtlasSize.height <= 0 || this->posAtlasSize.width <= 0)
		{
			this->posAtlasSize.height = 1;
			this->posAtlasSize.width = 1;
		}
	}
}}}
