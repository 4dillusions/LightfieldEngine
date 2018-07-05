/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSpriteFont.h"

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Render;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFSpriteFont::LFSpriteFont(const FontData &fontData, const LFString &textureName, LFRectangle &posVertexSize, LFRectangle &atlasPosSize) : 
		LFSprite(LFString(fontData.spriteFontName), textureName, posVertexSize, atlasPosSize),
		fontData(fontData)
    { }

	LFSpriteFont::~LFSpriteFont()
    { }

	void LFSpriteFont::Character(char character, const LFVector2D &atlasPos)
	{
		fontData.character = character;

		atlasPosSize.position = atlasPos;
		SetStartVertex();
	}
}}}}
