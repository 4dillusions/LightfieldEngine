#pragma once

#include "FGraphicsOpengl.h"
#include "..\\Core\\SMGameCompositComponent.h"
#include "..\\Core\\SMString.h"
#include "SMSprite.h"
#include "SMVertexBufferManager.h"

using namespace Osp::Graphics::Opengl;
using namespace SMEngine::Core;

namespace SMEngine { namespace Graphics
{
	class SMSpriteGroup : public SMGameCompositComponent
	{
	private:
		SMVertextTextureData *vertexTextureData;
		GLuint textureId;
		SMString groupCode;

	public:
		SMSpriteGroup(const SMString &groupCode);
		override ~SMSpriteGroup();

		override void Add(SMGameComponent *gameComponent); //SMSprite-ot vár
		override void Update(double deltaTime);
		override void WriteReport();
	};
};};
