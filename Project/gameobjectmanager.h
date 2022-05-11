#pragma once

#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_

#include <unordered_map>
#include <string>
#include "d3dclass.h"
#include "GameObject.h"
#include "GameEntity.h"
#include "Bullet.h"


class GameObjectManager {
public:
	GameObjectManager();
	GameObjectManager(const GameObjectManager&);
	~GameObjectManager();

	void AddGameObject(GameObject*, string);
	void RemoveGameObject(string);
	GameObject* GetGameObject(string);
	std::unordered_map<std::string, GameObject*> GetGameObjects();

	void Shutdown();

private:

	std::unordered_map<std::string, GameObject*> m_gameObjects;

};

#endif