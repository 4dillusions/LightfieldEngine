#include "SMTextureManager.h"
#include "FBase.h"
#include "FMedia.h"
#include "FGraphics.h"
#include "..\\Core\\SMCore.h"
#include "..\\IO\\SMLogger.h"

using namespace Osp::Base;
using namespace SMEngine::IO;
using namespace Osp::Graphics;
using namespace Osp::Media;

namespace SMEngine { namespace Graphics
{
	SMTextureManager *SMTextureManager::instance = nullptr;

	SMTextureManager::SMTextureManager()
	{ }

	void SMTextureManager::CreateInstance()
	{
		if (instance == nullptr)
			instance = new SMTextureManager();
	}

	void SMTextureManager::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	GLuint SMTextureManager::LoadBitmap(SMString pathAndName, bool isAlpha)
	{
		Image image; //<Privilege>  <Name>IMAGE</Name>  </Privilege>
		image.Construct();

		Bitmap *bitmap = image.DecodeN(pathAndName.ToBadaString(), BITMAP_PIXEL_FORMAT_ARGB8888);

		ByteBuffer *imageBuffer = image.EncodeToBufferN(*bitmap, IMG_FORMAT_BMP);
		int arrSize = imageBuffer->GetCapacity() - 54;

		byte *texture = new byte[arrSize];

		imageBuffer->SetPosition(54);
		imageBuffer->GetArray(texture, 0, arrSize);

		byte textureTemp;
		for (int i = 0; i < arrSize; i += 3)
		{
			textureTemp = texture[i];
			texture[i] = texture[i + 2];
			texture[i + 2] = textureTemp;
		}

		byte *textureWithAlpha;
		if (isAlpha)
		{
			textureWithAlpha = new byte[arrSize * 4 / 3];

			for (int src = 0, dst = 0; src < arrSize; src += 3, dst += 4)
			{
				// pixelek átmásolása
				textureWithAlpha[dst] = texture[src];
				textureWithAlpha[dst + 1] = texture[src + 1];
				textureWithAlpha[dst + 2] = texture[src + 2];

				// ha a pixel a lila szín, akkor az alfa = 0, egyébként 255.
				if (texture[src] == 255 && texture[src + 1] == 0 && texture[src + 2] == 255)
					textureWithAlpha[dst+3] = 0;
				else
					textureWithAlpha[dst+3] = 0xFF;
			}
		}

		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		if (isAlpha)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->GetWidth(), bitmap->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureWithAlpha);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap->GetWidth(), bitmap->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

		if (bitmap != 0) delete bitmap;
		if (imageBuffer != 0) delete imageBuffer;
		if (isAlpha && texture != 0) delete texture;

		return result;
	}

	GLuint SMTextureManager::LoadTexture(SMString texturePath, SMString textureName, bool isAlpha)
	{
		if (!textureDictionary.IsExist(textureName))
		{
			SMString pathAndName;
			pathAndName.Append(texturePath);
			pathAndName.Append(textureName);

			GLuint textureId = LoadBitmap(pathAndName, isAlpha);
			textureDictionary.Add(textureName, textureId);

			/*SMString text;
			text.Append("TextureManager: Add new texture: ");
			text.Append(textureName);
			SMLogger::Instance().WriteOutput(text);*/
		}
		else
		{
			/*SMString text;
			text.Append("TextureManager: Return old texture: ");
			text.Append(textureName);
			SMLogger::Instance().WriteOutput(text);*/
		}

		return textureDictionary[textureName];
	}

	void SMTextureManager::WriteReport()
	{
		SMLogger::Instance().WriteOutput("Texture list:");

		for (textureDictionary.First(); textureDictionary.IsDone(); textureDictionary.Next())
			SMLogger::Instance().WriteOutput(textureDictionary.CurrentKey());
	}
};};
