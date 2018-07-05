#pragma once

#include "..\\Core\\SMString.h"
#include "..\\Core\\SMContentManager.h"
#include <FIo.h>

using namespace Osp::Io;
using namespace SMEngine::Core;

namespace SMEngine { namespace IO
{
	/*
	struct, vagy egyéb adatszerkezetet lehet kiírni/olvasni file-ba/ból.

	Használat:
	struct TestData { int x[10]; };
	...
	TestData data;
	data.x[0] = 22;

	SMSerializer<TestData> ser;
	ser.WriteBinaryData("testData.dat", data);

	TestData data2 = ser.ReadBinaryData("testData.dat");
	*/
	template <typename T> class SMSerializer
	{
	public:
		void WriteBinaryData(const char *fileName, T &data)
		{
			SMString fileFullName;
			fileFullName.Append(SMContentManager::Instance().Path(SMContentManager::CP_OTHER));
			fileFullName.Append(fileName);

			#ifdef BADA_PLATFORM
			File file;
			file.Construct(fileFullName.ToBadaString(), "wb");
			file.Write((char *)&data, sizeof(T));
			#endif

			#ifdef WIN32_PLATFORM
			ofstream outfile(fileFullName.ToBadaChar(), ios::binary);
			outfile.write((char *)&data, sizeof(T));
			#endif
		}

		T ReadBinaryData(const char *fileName)
		{
			T result;

			SMString fileFullName;
			fileFullName.Append(SMContentManager::Instance().Path(SMContentManager::CP_OTHER));
			fileFullName.Append(fileName);

			#ifdef BADA_PLATFORM
			File file;
			file.Construct(fileFullName.ToBadaString(), "rb");
			file.Read((char *)&result, sizeof(T));
			#endif

			#ifdef WIN32_PLATFORM
			ifstream inFile(fileFullName.ToBadaString(), ios::binary);
			inFile.read((char *)&result, sizeof(T));
			#endif

			return result;
		}
	};
};};
