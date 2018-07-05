#pragma once

#include "FGraphicsOpengl.h"
#include "..\\Core\\SMDictionary.h"
#include "..\\Math\\SMVector2D.h"
#include "..\\Core\\SMSmartPtr.h"
#include "..\\Core\\SMString.h"

using namespace Osp::Graphics::Opengl;
using namespace SMEngine::Core;
using namespace SMEngine::Math;

namespace SMEngine { namespace Graphics
{
	struct SMVertextTextureData
	{
		GLfloat *vertexData, *textureData;
	};

	class SMVertexBufferManager
	{
	private:
		SMVertexBufferManager();

		static SMVertexBufferManager *instance;
		SMDictionary<SMString, SMSmartPtr<SMVertextTextureData> > vertexBufferDictionary;
		void InitVertexMatrix(SMVertextTextureData *vertexData, SMVector2D vertexSize, SMVector2D vertexMatrixSize);

	public:
		static SMVertexBufferManager *Instance() { return instance; }
		static void CreateInstance();
		static void ReleaseInstance();

		SMVertextTextureData *LoadVertexBuffer(const SMVector2D &vertexSize, const SMVector2D &vertexMatrixSize = SMVector2D());

		void WriteReport();
	};
};};
