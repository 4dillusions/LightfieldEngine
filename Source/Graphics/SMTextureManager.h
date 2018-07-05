#pragma once

#include "FGraphicsOpengl.h"
#include "..\\Core\\SMDictionary.h"
#include "..\\Core\\SMString.h"

using namespace Osp::Graphics::Opengl;
using namespace SMEngine::Core;

namespace SMEngine { namespace Graphics
{
	class SMTextureManager
	{
	private:
		SMTextureManager();

		static SMTextureManager *instance;
		SMDictionary<SMString, GLuint> textureDictionary;

		GLuint LoadBitmap(SMString pathAndName, bool isAlpha);

	public:
		static void CreateInstance();
		static void ReleaseInstance();
		static SMTextureManager *Instance() { return instance; }

		GLuint LoadTexture(SMString texturePath, SMString textureName, bool isAlpha);
		void WriteReport();
	};
};};
