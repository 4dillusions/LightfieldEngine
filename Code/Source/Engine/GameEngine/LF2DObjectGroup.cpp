/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LF2DObjectGroup.h"
#include "LF2DObject.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\Render\LFVertexTextureData.h"
#include "..\Render\LFTexture.h"

using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFEngine::Render;

namespace LFEngine { namespace GameEngine
{
    LF2DObjectGroup::LF2DObjectGroup(const LFString &groupCode) : LFGameCompositComponent(groupCode), vertexTextureData(nullptr),  texture(nullptr)
	{ }

	LF2DObjectGroup::~LF2DObjectGroup()
	{ }

	void LF2DObjectGroup::Add(LFGameComponent *lF2DObject)
	{
		LF2DObject *object = dynamic_cast<LF2DObject *>(lF2DObject);

		if (object == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LF2DObjectGroup::Add");
			return;
		}

		if (vertexTextureData == nullptr && texture == nullptr)
		{
			vertexTextureData = object->VertexTextureData();
			texture = object->Texture();
		}

		LFGameCompositComponent::Add(object);
	}

	void LF2DObjectGroup::Remove(LFGameComponent *lF2DObject)
	{
		LF2DObject *object = dynamic_cast<LF2DObject *>(lF2DObject);

		if (object == nullptr)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "nullptr LF2DObjectGroup::Remove");
			return;
		}

		LFGameCompositComponent::Remove(object);
	}

	void LF2DObjectGroup::Update(double deltaTime)
	{
		texture->Draw();
		vertexTextureData->Draw();

		LFGameCompositComponent::Update(deltaTime);
	}
}}
