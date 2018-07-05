/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFGameCompositComponent.h"

namespace LFEngine { namespace GameEngine
{
	class LFLayer;

	class LFENGINE_LIBRARY LFScreen : public LFCore::Common::LFGameCompositComponent
	{
	public:
		LFScreen(const LFCore::Common::LFString &name);
		virtual ~LFScreen();

		bool IsActive();
		void SetActive();
		LFLayer *FindLayer(const LFCore::Common::LFString &name);

		//LFGameCompositComponent
		void Add(LFGameComponent *lFLayer);
		void Remove(LFGameComponent *lFLayer);
	};
}}
