#include "SMGraphicsTest.h"
#include "..\\Graphics\\SMVertexBufferManager.h"
#include "..\\Graphics\\SMTextureManager.h"

#include "..\\Test\\SMTest.h"

using namespace SMEngine::Graphics;
using namespace SMEngine::Test;

namespace SMEngine { namespace Test
{
    void SMGraphicsTest::SMVbTest()
    {
    	SMVertextTextureData *data1 = SMVertexBufferManager::Instance()->LoadVertexBuffer(SMVector2D(10, 20));
    	SMVertextTextureData *data2 = SMVertexBufferManager::Instance()->LoadVertexBuffer(SMVector2D(10, 20));
    	SMVertextTextureData *data3 = SMVertexBufferManager::Instance()->LoadVertexBuffer(SMVector2D(10, 30));

    	SMTest::AssertOk(data1 == data2, "SMVertexBufferManager::LoadVertexBuffer again");
    	SMTest::AssertOk(data1 != data3, "SMVertexBufferManager::LoadVertexBuffer different");
    }

    void SMGraphicsTest::SMTextureTest()
    {
    	GLuint tex1 = SMTextureManager::Instance()->LoadTexture("/Home/Media/Images/BadaLogo.jpg", "BadaLogo", false);
    	GLuint tex2 = SMTextureManager::Instance()->LoadTexture("/Home/Media/Images/BadaLogo.jpg", "BadaLogo", false);
    	GLuint tex3 = SMTextureManager::Instance()->LoadTexture("/Home/Media/Images/basketball.png", "basketball", true);

        SMTest::AssertOk(tex1 == tex2, "SMTextureManager::LoadTexture again");
        SMTest::AssertOk(tex1 != tex3, "SMTextureManager::LoadTexture different");
    }
};};
