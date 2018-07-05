/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCurl.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFPatterns\LFIoc.h"

#ifdef WINCLASSIC
	#include "..\..\ThirdParty\_Win32_\cURL\curl.h"
#endif

#ifdef TIZEN
	#include <curl/curl.h>
#endif

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFNetwork
{
	char *LFCurl::response = nullptr;

	size_t LFCurl::OnResponse(void *ptr, size_t size, size_t nmemb, void *stream)
	{
		response = reinterpret_cast<char *>(ptr);

		return size * nmemb;
	}

	LFString LFCurl::GetResponse(const char *serverURL, const LFString &jsonRequest)
	{
		LFString result;
		response = nullptr;

		if (auto curl = curl_easy_init())
		{
			auto request = LFString(serverURL) + jsonRequest;
			request.Replace(LFString(" "), LFString("%20"));

			curl_easy_setopt(curl, CURLOPT_URL, request.ToChar());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnResponse);

			if (curl_easy_perform(curl) == CURLE_OK)
				result = response;
			else
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "LFCurl::GetResponse wrong post");

			curl_easy_cleanup(curl);
		}

		return result;
	}
}}}
