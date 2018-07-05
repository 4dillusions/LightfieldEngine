/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFGameComponentList.h"
#include "LFGameComponent.h"

namespace LFCore { namespace Common
{
	class LFCORE_LIBRARY LFGameCompositComponent : public LFGameComponent
	{
	protected:
		LFGameComponentList componentList;

	public:
		explicit LFGameCompositComponent(const LFString &name, bool isDestructDelete = true);
		virtual ~LFGameCompositComponent();

		virtual LFGameComponent *Find(const LFString &name);
		bool IsLastVisible(const LFString &name);
		int GetComponetsLength();
		void WriteOutputComponentNames();

		virtual void Add(LFGameComponent *gameComponent);
		virtual void Remove(LFGameComponent *gameComponent); //After render only
		
		//LFGameComponent
		virtual void Update(double deltaTime);
		virtual void SetIsAlive(bool isAlive);
		virtual void SetIsVisible(bool isVisible);
	};
}}
