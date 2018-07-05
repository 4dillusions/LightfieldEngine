/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFGameComponentList.h"
#include "LFGameComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFGameCompositeComponent : public LFGameComponent
	{
		LFGameCompositeComponent(const LFGameCompositeComponent&) = delete;
		LFGameCompositeComponent(LFGameCompositeComponent &&) = delete;
		LFGameCompositeComponent &operator=(const LFGameCompositeComponent &) = delete;
		LFGameCompositeComponent &operator=(LFGameCompositeComponent &&) = delete;

	protected:
		LFGameComponentList componentList;

	public:
		explicit LFGameCompositeComponent(const LFString &name, bool isDestructDelete = true);
		virtual ~LFGameCompositeComponent();

		virtual LFGameComponent *Find(const LFString &name);
		virtual LFGameComponent *Find(const LFGameComponent *gameComponent);
		bool IsLastVisible(const LFString &name);
		int GetComponentsLength() const;
		void WriteOutputComponentNames();

		virtual void Add(LFGameComponent *gameComponent);
		virtual void Remove(LFGameComponent *gameComponent); //After render only

		//LFGameComponent interface
		void Update(double deltaTime) override;
		void SetIsAlive(bool isAlive) override;
		void SetIsVisible(bool isVisible) override;
	};
}}}}