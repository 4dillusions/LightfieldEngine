/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMovableSpriteControl.h"
#include "..\LFCore\LFMath\LFMath.h"
#include "..\LFCore\LFCommon\LFSystemData.h"
#include "..\LFCore\LFCollections\LFLinkedList.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFCollections;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFRectangle LFMovableSpriteControl::walls;
	LFLinkedList<LFMovableSpriteControl *> LFMovableSpriteControl::movableSpriteList;

	void LFMovableSpriteControl::CCDCorrection(const LFMovableSpriteControl *anotherSprite)
	{
		//another movable sprite
		if (anotherSprite != nullptr)
		{
			float distance = boundingCircle.position.Distance(anotherSprite->boundingCircle.position);
			float diameter = boundingCircle.radius * 2;
			float difference = diameter - distance;
			
			LFVector2D circlesVector = anotherSprite->boundingCircle.position - boundingCircle.position;
			circlesVector.Normalizing();

			LFVector2D currentMove = position + circlesVector * -difference;

			SetPosition(currentMove);
		}

		//left/right walls
		SetPosition(LFVector2D(LFMath::Clamp(position.x, walls.GetLeft(), walls.GetRight() - boundingCircle.GetRadius() * 2.0f), position.y));

		//top wall
		auto top = walls.GetTop();
		if (position.y < top)
			SetPosition(LFVector2D(position.x, top));
	}

	LFMovableSpriteControl::LFMovableSpriteControl(const LFString &name, const LFRectangle &posVertexSize, const LFVector2D &posAtlas, float boundingRadius, const LFColor &color)
		: LFSpriteControl(name, posVertexSize, LFVector2D(posAtlas.x, posAtlas.y), false, color),
			boundingCircle(LFCircle(posVertexSize.position.x + boundingRadius, posVertexSize.position.y + boundingRadius, boundingRadius))
	{
		if (boundingCircle.radius > 0)
			movableSpriteList.Add(this);
	}

	LFMovableSpriteControl::~LFMovableSpriteControl()
	{
		for (movableSpriteList.First(); movableSpriteList.IsDone(); movableSpriteList.Next())
			if (movableSpriteList.GetCurrent() == this)
			{
				movableSpriteList.RemoveCurrent();
				break;
			}
	}

	void LFMovableSpriteControl::SetWalls(const LFRectangle &walls)
	{
		LFMovableSpriteControl::walls = walls;
	}

	void LFMovableSpriteControl::SetMove(const LFVector2D &move)
	{
		this->move = move;
		this->move.Normalizing();
		this->move *= 15;
	}

	void LFMovableSpriteControl::SetRefreshSpeed(double refreshSpeed)
	{
		this->refreshSpeed = refreshSpeed;
	}

	void LFMovableSpriteControl::SetPosition(const LFVector2D &position)
	{
		LFControl::SetPosition(position);
		boundingCircle.position = this->position + boundingCircle.GetRadius();
	}

	void LFMovableSpriteControl::Update(double deltaTime)
	{
		if (move.x != 0 && move.y != 0)
		{
			time += deltaTime;

			if (time > refreshSpeed) //refresh by speed
			{
				time = 0;

				//intersects wall bottom
				if (boundingCircle.position.y > walls.GetBottom() - boundingCircle.GetRadius())
				{
					move.Zero();

					return;
				}
				
				//intersects any MovableSprite in movableSpriteList
				for (movableSpriteList.First(); movableSpriteList.IsDone(); movableSpriteList.Next())
				{
					if (movableSpriteList.GetCurrent() != this && movableSpriteList.GetCurrent()->boundingCircle.Intersects(boundingCircle))
					{
						move.Zero();
						CCDCorrection(movableSpriteList.GetCurrent());

						OnSpriteTouch(SpriteTouchEventArgs{ movableSpriteList.GetCurrent() });

						return;
					}
				}
				
				//intersects left/right wall
				if (boundingCircle.position.x < walls.GetLeft() + boundingCircle.GetRadius() || boundingCircle.position.x > walls.GetRight() - boundingCircle.GetRadius())
					move.x = -move.x;

				//intersects top wall
				if (boundingCircle.position.y < walls.GetTop() + boundingCircle.GetRadius())
				{
					move.Zero();
					CCDCorrection();

					OnSpriteTouch(SpriteTouchEventArgs{ nullptr });

					return;
				}

				//move
				SetPosition(position + move);
			}
		}

		LFControl::Update(deltaTime);
	}
}}} 
