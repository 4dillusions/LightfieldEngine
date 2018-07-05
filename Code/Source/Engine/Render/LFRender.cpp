/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRender.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\Common\LFSystemInfo.h"
#include "..\..\Core\\Math\LFVector3D.h"

using namespace LFCore::Math;
using namespace LFCore::Common;
using namespace LFEngine::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Render
{
	LFRender *LFRender::instance = nullptr;

	LFRender::LFRender() : backgroundColor(LFColor(51, 51, 51))
	{
		LFString text;
		text += "Create render ";
		text += LFSystemInfo::Render();
		LFLogger::Instance().WriteOutput(text);
	}

	LFRender::~LFRender()
	{
		LFString text;
		text += "Release render ";
		text += LFSystemInfo::Render();
		LFLogger::Instance().WriteOutput(text);
	}

	LFRender::LFRenderType LFRender::RenderType()
	{
		LFString renderType(LFSystemInfo::Render());
		LFRenderType result;

		if (renderType == LFString("OpenGL11"))
			result = LFRender::RT_OpenGL11;
		else if (renderType == LFString("Direct3D9"))
			result = LFRender::RT_Direct3D9;

		return result;
	}
}}
