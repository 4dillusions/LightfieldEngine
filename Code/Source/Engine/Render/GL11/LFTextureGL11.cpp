/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTextureGL11.h"
#include "..\..\..\Depencies\Soil\SOIL.h"
#include "..\..\..\Core\IO\LFLogger.h"
#include "..\..\..\Core\Common\LFString.h"

#ifdef TIZEN
#include <Elementary_GL_Helpers.h>
#include "../_Tizen_/LFRenderWindowTizen.h"
#endif

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFTextureGL11::LFTextureGL11() 
	#ifdef TIZEN
		: glview(nullptr)
	#endif
	{ }

	LFTextureGL11::~LFTextureGL11()
	{ }

	void LFTextureGL11::CreateTexture(const LFCore::Common::LFString &textureName)
	{
		#ifdef TIZEN
		if (glview == nullptr)
			glview = ((LFRenderWindowTizen *)LFRenderWindow::Instance())->GlView();

		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glGenTextures(1, &textureIndex);
		glBindTexture(GL_TEXTURE_2D, textureIndex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		unsigned char *texture = SOIL_load_image(textureName.ToChar(), &textureWidth, &textureHeight, 0, SOIL_LOAD_RGBA);
		bool isTextureNull = (texture == nullptr);
		if (!CheckTexture(isTextureNull))
			return;

		CheckTextureSize();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		SOIL_free_image_data(texture);

		LFString log;
		log += "Create new texture: ";
		log += textureName;
		LFLogger::Instance().WriteOutput(log);

		dataList.Add(textureName, this);
	}

	void LFTextureGL11::Draw()
	{
		#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
		#endif

		glBindTexture(GL_TEXTURE_2D, textureIndex);
	}
}}
