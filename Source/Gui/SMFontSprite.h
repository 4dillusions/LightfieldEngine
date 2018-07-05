#pragma once

#include "..\\Graphics\\SMSprite.h"
#include "..\\IO\\SMSerializer.h"

using namespace SMEngine::Graphics;

namespace SMEngine { namespace Gui
{
	struct CharData
	{
		int vertexIndex;
		int charWidth;
	
		CharData()
		{ }

		CharData(int vertexIndex, int charWidth) : vertexIndex(vertexIndex), charWidth(charWidth)
		{ }
	};

	struct CharDat
	{
		CharData data[100];
	};

	/*
	FontSprite: Belsõ használatra controlokban lévõ szövegekhez,

	Használat (belsõleg controlokhoz, csak a teszt kedvéért lehet így is):

	SMFontSprite *font = new SMFontSprite('A', 30, SMVector2D(), "Font.png");
	spriteLayer->Add(font);
	*/
	class SMFontSprite : public SMSprite
	{
	private:
		SMSerializer<CharDat> serializer;
		static CharDat charDat;
		static bool initialized;
		CharData charData;
		int vertexIndex; //a quad mátrixban a font vertex indexe
		char character; //melyik betût tárolja, jeleníti meg

	public:
		SMFontSprite(char character, int size, const SMVector2D &position, const SMString &textureName, bool isVisible = true);

		int CharWidth() const { return charData.charWidth; }
		char Character() { return character; }
		void Character(char character);

		override void Update(double deltaTime);
	};
};};
