#include "SMContentManager.h"

namespace SMEngine { namespace Core
{
	SMContentManager SMContentManager::instance;

	void SMContentManager::AddPath(const ContentPath &pathEnum, SMString path)
	{
		contentPathList.Add(pathEnum, path);
	}

	SMString SMContentManager::Path(const ContentPath &pathEnum)
	{
		return contentPathList[pathEnum];
	}
};};
