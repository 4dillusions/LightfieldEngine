/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLayer.h"
#include "LF2DObject.h"
#include "LFControl.h"
#include "..\Graphics\LF2D\LFSprite.h"
#include "LF2DObjectGroup.h"
#include "..\..\Core\\IO\LFLogger.h"

using namespace LFEngine::Graphics::LF2D;
using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace GameEngine
{
	LFLayer::LFLayer(const LFString &name) : LFGameCompositComponent(name), screen(nullptr)
    { }

	LFLayer::~LFLayer()
    { }

	LF2DObject *LFLayer::Find2DObject(const LFString &name)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
		{
			LFGameComponent *current = componentList.Current();

			if (LFControl *control = dynamic_cast<LFControl *>(current))
				if (control->GetName() == name)
					return dynamic_cast<LF2DObject *>(control);

			if (LF2DObjectGroup *group = dynamic_cast<LF2DObjectGroup *>(current))
				if (LFSprite *sprite = dynamic_cast<LFSprite *>(group->Find(name)))
					return dynamic_cast<LF2DObject *>(sprite);
		}

		return nullptr;
	}

	void LFLayer::AddSprite(LFSprite *sprite)
	{
		LFString groupCode = sprite->GroupCode();
		LF2DObjectGroup *group = (LF2DObjectGroup *)Find(groupCode);

		if (group == nullptr)
		{
			group = LFNew<LF2DObjectGroup>(AT, groupCode);
			LFGameCompositComponent::Add(group);
		}

		group->Add(sprite);
	}

	void LFLayer::AddControl(LFControl *control)
	{
		LFGameCompositComponent::Add(control);
	}

	void LFLayer::Add(LFGameComponent *lF2DObject)
	{
		LF2DObject *object = dynamic_cast<LF2DObject *>(lF2DObject);

		if (object == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LFLayer::Add");
			return;
		}

		if (LFSprite *sprite = dynamic_cast<LFSprite *>(object))
			AddSprite(sprite);
		
		if (LFControl *control = dynamic_cast<LFControl *>(object))
			AddControl(control);

		object->Layer(this);
	}

	void LFLayer::Remove(LFGameComponent *lF2DObject)
	{
		LF2DObject *object = dynamic_cast<LF2DObject *>(lF2DObject);

		if (object == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LFLayer::Remove");
			return;
		}

		if (LF2DObjectGroup *group = (LF2DObjectGroup *)Find(object->GroupCode()))
			group->Remove(object);
	}

	void LFLayer::SetIsVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}
}}
