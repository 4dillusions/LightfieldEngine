#include "SMSpriteGroup.h"
#include "..\\IO\\SMLogger.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Graphics
{
	SMSpriteGroup::SMSpriteGroup(const SMString &groupCode) :
			textureId(0), vertexTextureData(nullptr), groupCode(groupCode), SMGameCompositComponent(groupCode)
	{ }

	SMSpriteGroup::~SMSpriteGroup()
	{ }

	void SMSpriteGroup::Add(SMGameComponent *gameComponent)
	{
		if (SMSprite *sprite = dynamic_cast<SMSprite *>(gameComponent))
		{
			if (textureId == 0 || vertexTextureData == nullptr)
			{
				textureId = sprite->TextureId();
				vertexTextureData = sprite->VertexTextureData();
			}

			SMGameCompositComponent::Add(gameComponent);
		}
	}

	void SMSpriteGroup::Update(double deltaTime)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		glVertexPointer(2, GL_FLOAT, 0, vertexTextureData->vertexData);
		glTexCoordPointer(2, GL_FLOAT, 0, vertexTextureData->textureData);

		SMGameCompositComponent::Update(deltaTime);
	}

	void SMSpriteGroup::WriteReport()
	{
		SMString text;
		text.Append(groupCode);
		SMLogger::Instance().WriteOutput(text);
	}
};};
