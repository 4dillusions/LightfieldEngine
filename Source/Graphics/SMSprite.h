#pragma once

#include "FGraphicsOpengl.h"
#include "..\\Graphics\\SMVertexBufferManager.h"
#include "..\\Core\\SMGameComponent.h"
#include "..\\Math\\SMVector2D.h"
#include "..\\Core\\SMString.h"
#include "..\\Graphics\\SMTextureManager.h"

using namespace Osp::Graphics::Opengl;
using namespace SMEngine::Graphics;
using namespace SMEngine::Core;
using namespace SMEngine::Math;

namespace SMEngine { namespace Graphics
{
	/*
	Használat:

	SMSprite *badaLogo = new SMSprite(SMVector2D(256, 256), SMVector2D(20, 20), "BadaLogo.jpg");
	spriteLayer->Add(badaLogo);
	*/
	class SMSprite : public SMGameComponent
	{
	protected:
		SMVertextTextureData *vertexTextureData;
		GLuint textureId;
		SMVector2D size, offset, position;
		SMString groupCode;
		bool isVisible;

	public:
		SMSprite(const SMVector2D &size, const SMVector2D &position, SMString textureName, bool isAlpha = false, bool isVisible = true, bool isFont = false);
		override ~SMSprite();

		GLuint TextureId() const { return textureId; }
		SMVertextTextureData *VertexTextureData() const { return vertexTextureData; }
		SMString &GroupCode() { return groupCode; }
		void Position(const SMVector2D &position);
		SMVector2D Position();
		void PositionOffset(const SMVector2D &position);

		override void Update(double deltaTime);
	};
};};
