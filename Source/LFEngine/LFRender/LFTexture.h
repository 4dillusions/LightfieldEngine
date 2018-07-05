/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFRenderComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFTexture : public LFRenderComponent
	{
	protected:
		int textureWidth = 0, textureHeight = 0;

	public:
		explicit LFTexture(const LFCore::LFCommon::LFString &textureName);
		virtual ~LFTexture() = default;

		int GetTextureWidth() const;
		int GetTextureHeight() const;

		bool CheckTexture(bool isTextureNull) const;
		bool CheckTextureSize() const;

		static LFCore::LFCommon::LFString CreateName(const LFCore::LFCommon::LFString &textureName);

		//LFRenderComponent functions
		bool Create() override = 0;
		void BeginRender() override = 0;
		void Draw() override = 0;
		void EndRender() override = 0;
		void Release() override;
	};
}}}
