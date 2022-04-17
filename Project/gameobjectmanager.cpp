#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

	m_gameObjects.clear();
}

GameObjectManager::GameObjectManager(const GameObjectManager&)
{
}

GameObjectManager::~GameObjectManager()
{
}


void GameObjectManager::AddGameObject(GameObject* gameobj, string gameobjname)
{
	m_gameObjects.insert({ gameobjname, gameobj });			// LHS name RHS gameobject !!
}


GameObject* GameObjectManager::GetGameObject(string gameobjname)
{
	
	return  m_gameObjects.at(gameobjname);
}

std::unordered_map<std::string, GameObject*> GameObjectManager::GetGameObjects()
{
	return m_gameObjects;
}

void GameObjectManager::Shutdown()
{
	for (auto& it : m_gameObjects) {
		GameObject* gameObject;

		gameObject = m_gameObjects.at(it.first);

		gameObject->ReleaseObject();

	}
	m_gameObjects.clear();

}

