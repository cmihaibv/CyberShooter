#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameEntity.h"

using namespace std;


class Bullet : public GameObject
{
public:
	bool Alive()
	{
		if (distanceCount == 100)
		{
			return false;
		}
		return true;
	}
	void Action() override
	{
		//MoveForward
		XMVECTOR move = GetForwardVector() * 0.15f;

		distanceCount += 1;
		UpdatePosition(move);
	}
protected:
	int distanceCount = 0;
};

#endif