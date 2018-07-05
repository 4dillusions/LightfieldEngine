/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"

namespace LFEngine { namespace GameEngine
{
	class LFGameEngineHelper
	{
	public:
		void CreateRender();
		void ReleaseRender();
		void CreateRenderWindow();
		void ReleaseRenderWindow();
		void CreateInput();
		void ReleaseInput();
		void CreateAudio();
		void ReleaseAudio();
	};
}}
