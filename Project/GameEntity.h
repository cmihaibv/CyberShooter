#pragma once
#ifndef _GAMEENTITY_H_
#define _GAMEENTITY_H_

#include "GameObject.h"

using namespace std;


class GameEntity: public GameObject
{
public:
	void Action();

};

#endif