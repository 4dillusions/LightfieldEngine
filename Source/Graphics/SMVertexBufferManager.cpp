#include "SMVertexBufferManager.h"
#include "FBase.h"
#include "..\\IO\\SMLogger.h"

using namespace Osp::Base;
using namespace SMEngine::IO;

namespace SMEngine { namespace Graphics
{
	SMVertexBufferManager *SMVertexBufferManager::instance = nullptr;

	SMVertexBufferManager::SMVertexBufferManager()
	{ }

	void SMVertexBufferManager::CreateInstance()
	{
		if (instance == nullptr)
			instance = new SMVertexBufferManager();
	}

	void SMVertexBufferManager::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	/*
	Vertex mátrix módszer:

	Egy nagy vertex buffer quadokra van osztva (2-2 triangle 1 quad és triangle list-ekbõl áll az egész) a textúrán lévõ négyzetrácsnak megfelelõen.
	Minden quad ugyanabban a pozícióban van, de a textúra szét van osztva közöttük.
	Rajzolásnál elég csak az indexet megadni honnantól kezdve rajzolja ki a quadot és bármelyik darab kirajzolható ugyanabban a pozícióban.
	Így lehet statikus font, vagy akár animált sprite a kirajzolt objektum tetszés szerint viszonylag gyors rendereléssel.
	*/
	void SMVertexBufferManager::InitVertexMatrix(SMVertextTextureData *vertexData, SMVector2D vertexSize, SMVector2D vertexMatrixSize)
	{
		vertexData->vertexData = new GLfloat[(int)vertexMatrixSize.x * (int)vertexMatrixSize.y * 12];
		vertexData->textureData = new GLfloat[(int)vertexMatrixSize.x * (int)vertexMatrixSize.y * 12];

		/*
		1*(-1, 1)   3*(1, 1)

		0*(-1, -1)   2*(1, -1)
		*/
		GLfloat vertices[] =
		{
			-vertexSize.x, -vertexSize.y, //0
			-vertexSize.x, vertexSize.y, //1
			vertexSize.x, -vertexSize.y, //2
			-vertexSize.x, vertexSize.y, //1
			vertexSize.x, vertexSize.y, //3
			vertexSize.x, -vertexSize.y //2
		};

		for (int quads = 0, index = 0; quads < vertexMatrixSize.x * vertexMatrixSize.y; ++quads)
			for (int verts = 0; verts < 12; ++verts, ++index)
				vertexData->vertexData[index] = vertices[verts];

		GLfloat coords[] =
		{
			0.0f, 0.0f, //0
			0.0f, 1.0f, //1
			1.0f, 0.0f, //2
			0.0f, 1.0f, //1
			1.0f, 1.0f, //3
			1.0f, 0.0f //2
		};

		float stepX = (1 / vertexMatrixSize.x);
		float stepY = (1 / vertexMatrixSize.y);

		for (int x = vertexMatrixSize.x - 1, index = 0; x > - 1; --x)
			for (int y = 0; y < vertexMatrixSize.y; ++y)
				for (int verts = 0; verts < 12; ++verts, ++index)
				{
					if (verts % 2 == 0)
						vertexData->textureData[index] = ((coords[verts] + y) * stepY);
					else
						vertexData->textureData[index] = ((coords[verts] + x) * stepX);
				}
	}

	SMVertextTextureData *SMVertexBufferManager::LoadVertexBuffer(const SMVector2D &vertexSize, const SMVector2D &vertexMatrixSize)
	{
		bool isVertexMatrix = (vertexMatrixSize.x > 1 || vertexMatrixSize.y > 1);

		SMString vbCode;
		vbCode.Append(vertexSize.x);
		vbCode.Append("_");
		if (isVertexMatrix) vbCode.Append("matrix_");
		vbCode.Append(vertexSize.y);

		if (!vertexBufferDictionary.IsExist(vbCode))
		{
			SMSmartPtr<SMVertextTextureData> vertexTextureData(new SMVertextTextureData());

			if (isVertexMatrix) //Vertex Matrix módszer
			{
				InitVertexMatrix(vertexTextureData, vertexSize, vertexMatrixSize);
			}
			else
			{
				/*
				1*(-1, 1)   3*(1, 1)

				0*(-1, -1)   2*(1, -1)
				*/
				GLfloat vertices[] =
				{
					-vertexSize.x, -vertexSize.y, //0
					-vertexSize.x, vertexSize.y, //1
					vertexSize.x, -vertexSize.y, //2
					vertexSize.x, vertexSize.y //3
				};

				GLfloat *vertexData = new GLfloat[8];
				memcpy(vertexData, vertices, sizeof(vertices));

				GLfloat coords[] =
				{
					0.0f, 0.0f, //0
					0.0f, 1.0f, //1
					1.0f, 0.0f, //2
					1.0f, 1.0f //3
				};

				GLfloat *textureData = new GLfloat[8];
				memcpy(textureData, coords, sizeof(coords));

				vertexTextureData->vertexData = vertexData;
				vertexTextureData->textureData = textureData;
			}

			vertexBufferDictionary.Add(vbCode, vertexTextureData);

			/*SMString text;
			if (vertexMatrixSize.x > 1 || vertexMatrixSize.y > 1)
				text.Append("VertexBufferManager: Add new vertex matrix buffer: ");
			else
				text.Append("VertexBufferManager: Add new vertex buffer: ");

			text.Append(vbCode);
			SMLogger::Instance().WriteOutput(text);*/
		}
		else
		{
			SMString text;
			/*text.Append("VertexBufferManager: Return old vertex buffer: ");
			text.Append(vbCode);
			SMLogger::Instance().WriteOutput(text);*/
		}

		return vertexBufferDictionary[vbCode];
	}

	void SMVertexBufferManager::WriteReport()
	{
		SMLogger::Instance().WriteOutput("VB list:");

		for (vertexBufferDictionary.First(); vertexBufferDictionary.IsDone(); vertexBufferDictionary.Next())
			SMLogger::Instance().WriteOutput(vertexBufferDictionary.CurrentKey());
	}
};};
