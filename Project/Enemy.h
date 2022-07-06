#pragma once

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"


class Enemy: public GameObject
{
public:


	Enemy();


	void Action() override;
	void Action(GameObject& obj) override;
	void Action(GameObject* obj) override;
	State GetState() override;


private:
	
	float m_detectionDistance=15.0f;
	float m_attackDistance=10.0f;
	GameObject* m_target;
};

#endif


