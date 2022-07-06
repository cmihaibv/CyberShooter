#pragma once

#include <DirectXMath.h>
#include <unordered_map>
#include <string>
#include "gameobjectmanager.h"

/// <summary>
/// Objects of type gameobject accepted.
/// </summary>
/// <typeparam name="T"></typeparam>
//template <class T, class H>
//class CollisionEngine
//{
//public:
//	CollisionEngine(T);
//	CollisionEngine(const CollisionEngine&);
//	~CollisionEngine();
//
//	float CalculateDistance(DirectX::XMVECTOR, DirectX::XMVECTOR);
//	std::string TestCollision();
//
//private:
//	std::unordered_map<std::string,H*>* m_objects;
//	float m_sphereradius;
//};

class CollisionEngine
{
public:
	CollisionEngine();
	CollisionEngine(const CollisionEngine&);
	~CollisionEngine();

	void SetGameObjectManager(GameObjectManager*);

	float CalculateDistance(DirectX::XMVECTOR, DirectX::XMVECTOR);
	std::vector<std::string> TestCollision();

private:
	 GameObjectManager* m_gameObjects;
	float m_sphereradius;

};