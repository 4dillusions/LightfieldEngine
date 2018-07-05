#include "SMAnimatableSprite.h"

namespace SMEngine { namespace Gui
{
	SMAnimatableSprite::SMAnimatableSprite(const SMVector2D &frameSize, const SMVector2D &textureSize, const SMVector2D &position, const SMString &textureName,
		const SMVector2D &matrixSize, bool isVisible) :
			SMSprite(frameSize, position, textureName, true, isVisible, true), vertexIndex(0), isForward(true), isAnimating(true), isFirstUse(true)
	{
		frameCout = (int)(matrixSize.y * matrixSize.x);
		vertexCout = frameCout * 6;
		vertexTextureData = SMVertexBufferManager::Instance()->LoadVertexBuffer(frameSize, SMVector2D(matrixSize.y, matrixSize.x)); //az ogl miatt van fordítva a mátrix felosztása
	}

	void SMAnimatableSprite::IsForward(bool isForward)
	{
		this->isForward = isForward;

		if (isForward) vertexIndex = 0;
		else vertexIndex = vertexCout - 6;
	}

	void SMAnimatableSprite::IsKillMe(bool isKillMe)
	{
		this->isKillMe = isKillMe;
		if (isKillMe) isLoop = false;
	}

	void SMAnimatableSprite::PlayAnim()
	{
		isFirstUse = false;

		if (isAnimating == false)
		{
			isAnimating = true;

			if (isForward) vertexIndex = 0;
			else vertexIndex = vertexCout - 6;
		}
	}

	void SMAnimatableSprite::Update(double deltaTime)
	{
		glPushMatrix();
			glTranslatef(position.x, position.y, 0.0f);
			glDrawArrays(GL_TRIANGLES, vertexIndex, 6);
		glPopMatrix();


		if (!isFirstUse)
		{
			time += timer.DeltaTime();

			if (time > speedTime)
			{
				time = 0;

				if (isForward)
				{
					if (vertexIndex < vertexCout - 6) vertexIndex += 6;

					if (isLoop)
					{
						if (vertexIndex == vertexCout - 6) //vége az animnak és loop van
							vertexIndex = 0;
					}
					else if (vertexIndex == vertexCout - 6) //vége az animnak és nincs loop
					{
						isAnimating = false;
						if (isKillMe) SMSprite::IsAlive(false);
					}
				}
				else
				{
					if (vertexIndex > 0) vertexIndex -= 6;

					if (isLoop)
					{
						if (vertexIndex == 0) //vége az animnak és loop van
							vertexIndex = vertexCout - 6;
					}
					else if (vertexIndex == 0) //vége az animnak és nincs loop
					{
						isAnimating = false;
						if (isKillMe) SMSprite::IsAlive(false);
					}
				}
			}
		}
	}
};};
