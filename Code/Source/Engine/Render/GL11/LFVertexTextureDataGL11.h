/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFVertexTextureData.h"

#ifdef WIN32
#include "..\..\..\..\Source\Depencies\Glfw\SDK\include\GLFW\glfw3.h"
#endif

#ifdef TIZEN
#include <Elementary.h>
#endif

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFVertexTextureDataGL11 : public LFVertexTextureData
	{ 
	private:
		#ifdef TIZEN
		Evas_Object *glview;
		#endif

		GLfloat *vertexData;
		GLfloat *textureData;
		static const int verticesCount = 12;

		void CreateVertexAtlasData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);
		void CreateTextureAtlasData(const LFCore::Math::LFVector2D &atlasSize);

	public:
		LFVertexTextureDataGL11();
		virtual ~LFVertexTextureDataGL11();

		virtual void CreateVertexTextureData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);
		virtual void Draw();
	};
}}
