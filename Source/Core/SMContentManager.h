#pragma once

#include "SMDictionary.h"
#include "SMString.h"

namespace SMEngine { namespace Core
{
	/*
	A contentek elérési útvonalát manageli
	*/
	class SMContentManager
	{
	public:
		enum ContentPath { CP_IMAGE, CP_SOUND, CP_OTHER };

	private:
		static SMContentManager instance;

		SMDictionary<ContentPath, SMString> contentPathList;

	public:
		static SMContentManager &Instance() { return instance; }

		void AddPath(const ContentPath &pathEnum, SMString path);
		SMString Path(const ContentPath &pathEnum);
	};
};};
