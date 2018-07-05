#include "SMFontSprite.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Gui
{
	CharDat SMFontSprite::charDat;
	bool SMFontSprite::initialized = false;

	SMFontSprite::SMFontSprite(char character, int size, const SMVector2D &position, const SMString &textureName, bool isVisible) :
		SMSprite(SMVector2D(size, size), position, textureName, true, isVisible, true)
	{
		if (initialized == false) //csak egyszer töltõdik be a font data
		{
			charDat = serializer.ReadBinaryData("font.dat");
			initialized = true;
		}

		Character(character);
		vertexTextureData = SMVertexBufferManager::Instance()->LoadVertexBuffer(SMVector2D(size, size), SMVector2D(4, 16)); //az ogl miatt van fordítva a mátrix felosztása
	}

	void SMFontSprite::Character(char character)
	{
		this->character = character;
		charData = charDat.data[(int)character];
		vertexIndex = charData.vertexIndex;
	}

	void SMFontSprite::Update(double deltaTime)
	{
		glPushMatrix();
			glTranslatef(position.x, position.y, 0.0f);
			glDrawArrays(GL_TRIANGLES, vertexIndex, 6);
		glPopMatrix();
	}
};};
