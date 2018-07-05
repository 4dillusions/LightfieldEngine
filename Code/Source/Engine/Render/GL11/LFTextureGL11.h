/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFTexture.h"

#ifdef WIN32
#include "..\..\..\..\Source\Depencies\Glfw\SDK\include\GLFW\glfw3.h"
#else
#include <Elementary.h>
#endif

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFTextureGL11 : public LFTexture
	{ 
	private:
		GLuint textureIndex;

		#ifdef TIZEN
		Evas_Object *glview;
		#endif

	public:
		LFTextureGL11();
		virtual ~LFTextureGL11();

		virtual void CreateTexture(const LFCore::Common::LFString &textureName);
		virtual void Draw();
	};
}}
