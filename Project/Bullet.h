#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameEntity.h"

using namespace std;


class Bullet : public GameObject
{
public:
	void Action() override
	{
		//MoveForward
		XMVECTOR move = GetForwardVector() * 0.01f;

		UpdatePosition(move);
	}

};

#endif