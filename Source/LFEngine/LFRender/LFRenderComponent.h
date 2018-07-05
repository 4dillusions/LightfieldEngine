/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFString.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	class LFVFSManager;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFRenderComponent
	{
	protected:
		LFCore::LFCommon::LFString name;
		LFCore::LFCommon::LFVFSManager *vfsManager;

	public:
		explicit LFRenderComponent(const LFCore::LFCommon::LFString &name);
		virtual ~LFRenderComponent() = default;

		const LFCore::LFCommon::LFString &GetName() const;

		virtual bool Create() = 0;
		virtual void BeginRender() = 0;
		virtual void Draw() = 0;
		virtual void EndRender() = 0;
		virtual void Release() = 0;
	};
}}}
