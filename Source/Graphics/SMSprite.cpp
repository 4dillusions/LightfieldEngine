#include "SMSprite.h"
#include "..\\Engine\\SMSystemInfo.h"
#include "..\\Core\\SMContentManager.h"
#include "..\\IO\\SMLogger.h"

using namespace SMEngine::Engine;
using namespace SMEngine::IO;

namespace SMEngine { namespace Graphics
{
	SMSprite::SMSprite(const SMVector2D &size, const SMVector2D &position, SMString textureName, bool isAlpha, bool isVisible, bool isFont)
		: size(size), position(position), SMGameComponent(textureName)
	{
		SMString groupCode;
		groupCode.Append(size.x);
		groupCode.Append("_");
		groupCode.Append(size.y);
		groupCode.Append("_");
		groupCode.Append(textureName);

		this->groupCode = groupCode;

		textureId = SMTextureManager::Instance()->LoadTexture(SMContentManager::Instance().Path(SMContentManager::CP_IMAGE), textureName, isAlpha);

		if (!isFont)
			vertexTextureData = SMVertexBufferManager::Instance()->LoadVertexBuffer(size);

		offset.x = ((SMSystemInfo::Instance().ScreenWidth() / 2.0f) - (size.x / 2.0f)) * 2;
		offset.y = -((SMSystemInfo::Instance().ScreenHeight() / 2.0f) - (size.y / 2.0f)) * 2;

		Position(position);
	}

	SMSprite::~SMSprite()
	{ }

	void SMSprite::Position(const SMVector2D &position)
	{
		this->position.x = position.x * 2;
		this->position.y = -position.y * 2;
		this->position -= offset; //transzformáció a screen koordináta rendszerbõl openGL-be

		/*glPushMatrix();
			glTranslatef(this->position.x, this->position.y, 0.0f);
		glPopMatrix();*/
	}

	SMVector2D SMSprite::Position()
	{
		return SMVector2D(position.x + offset.x, -(position.y + offset.y)) / 2.0f; //transzformálás openGL koordináta rendszerbõl screen-be
	}

	void SMSprite::PositionOffset(const SMVector2D &position)
	{
		this->position += (SMVector2D(position.x, -position.y) * 2);
	}

	void SMSprite::Update(double deltaTime)
	{
		glPushMatrix();
			glTranslatef(position.x, position.y, 0.0f);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glPopMatrix();
	}
};};
