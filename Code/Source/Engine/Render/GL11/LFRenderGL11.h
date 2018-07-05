/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFRender.h"

#ifdef WIN32
struct GLFWwindow;
#endif

#ifdef TIZEN
#include <Elementary.h>
#endif

namespace LFEngine { namespace Render { namespace GL11
{
	class LFENGINE_LIBRARY LFRenderGL11 : public LFEngine::Render::LFRender
	{ 
	private:
		#ifdef WIN32
		GLFWwindow *window;
		#endif

		#ifdef TIZEN
		Evas_Object *glview;
		#endif

	public:
		LFRenderGL11();
		virtual ~LFRenderGL11();

		static void CreateInstance();
		static void ReleaseInstance();

		//LFRender
		virtual void Init();
		virtual void BeginScene();
		virtual void EndScene();
		virtual LFVertexTextureData *CreateVertexTextureData(const LFCore::Math::LFVector2D &vertexSize, const LFCore::Math::LFVector2D &atlasSize);
		virtual LFTexture *CreateTexture(const LFCore::Common::LFString &textureName);
		virtual void OffsetRelativePosition(LFCore::Math::LFRectangle &posVertexSize);
		virtual void Draw2DObject(const LFCore::Math::LFVector2D &position, int startVertex);
	};
}}}
