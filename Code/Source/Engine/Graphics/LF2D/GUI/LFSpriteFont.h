/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFSprite.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class FontData
	{
	public:
		char character;
		const char *spriteFontName;
	};

	class LFSpriteFont : public LFEngine::Graphics::LF2D::LFSprite
	{
	private:
		FontData fontData;

	public:
		LFSpriteFont(const FontData &fontData, const LFCore::Common::LFString &textureName, LFCore::Math::LFRectangle &posVertexSize, LFCore::Math::LFRectangle &atlasPosSize);
		virtual ~LFSpriteFont();

		FontData &GetFontData() { return fontData; }
		char Character() { return fontData.character; }
		void Character(char character, const LFCore::Math::LFVector2D &atlasPos);
	};
}}}}
