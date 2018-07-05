/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFGameEngine
{
	/** 
		@brief 
		GameEngineFactory creates or releases platform specific subsystems
	*/
	class LF3GameEngineFactory final
	{
		LF3GameEngineFactory() = delete;
		LF3GameEngineFactory(const LF3GameEngineFactory&) = delete;
		LF3GameEngineFactory(LF3GameEngineFactory &&) = delete;
		LF3GameEngineFactory &operator=(const LF3GameEngineFactory &) = delete;
		LF3GameEngineFactory &operator=(LF3GameEngineFactory &&) = delete;
		~LF3GameEngineFactory() = delete;

	public:
		static void CreateRenderSystem();
		static void ReleaseRenderSystem();
		static void CreateRenderComponentList();
		static void ReleaseRenderComponentList();
		static void CreateRenderWindow();
		static void ReleaseRenderWindow();
		static void CreateInput();
		static void ReleaseInput();
		static void CreateAudio();
		static void ReleaseAudio();
	};
}}}
