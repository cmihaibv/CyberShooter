#include "CollisionEngine.h"


//template<class T, class H>
//CollisionEngine<T,H>::CollisionEngine(T objects)
//{
//	m_objects = objects;
//}
//template<class T, class H>
//CollisionEngine<T,H>::CollisionEngine(const CollisionEngine&)
//{
//}
//template<class T, class H>
//CollisionEngine<T,H>::~CollisionEngine()
//{
//}
//template<class T, class H>
//float CollisionEngine<T, H>::CalculateDistance(DirectX::XMVECTOR vec1,DirectX::XMVECTOR vec2)
//{
//	DirectX::XMFLOAT3 object1;
//	DirectX::XMStoreFloat3(&object1, vec1);
//	DirectX::XMFLOAT3 object2;
//	DirectX::XMStoreFloat3(&object2, vec2);
//	float distance = sqrt((object1.x + object2.x) * (object1.x + object2.x)
//						+ (object1.y + object2.y) * (object1.y + object2.y)
//						+ (object1.z + object2.z) * (object1.z + object2.z));
//	return distance;
//}
//
//template<class T, class H>
//std::string CollisionEngine<T,H>::TestCollision()
//{	//get Object from the obj manager
//	for (int i = 0; i < m_objects->GetGameObjects().size();i++) {
//
//		//get the next GameObject the obj manager
//		for (int j = i + 1; j < m_objects->GetGameObjects().size(); j++)
//		{
//			float distance = CalculateDistance(m_objects[i]->GetPositionVec(), m_object[j]->GetPositionVec());
//			if (distance < m_objects[i]->GetCollisionSphere()->GetRadius() || distance < m_objects[i]->GetCollisionSphere()->GetRadius())
//			{
//				return std::vector<std::string> names
//			}
//			
//		}
//	}
//}


CollisionEngine::CollisionEngine()
{
	
}

CollisionEngine::CollisionEngine(const CollisionEngine&)
{
}

CollisionEngine::~CollisionEngine()
{
}

void CollisionEngine::SetGameObjectManager(GameObjectManager* objmanager)
{
	m_gameObjects = objmanager;
}

float CollisionEngine::CalculateDistance(DirectX::XMVECTOR vec1, DirectX::XMVECTOR vec2)
{
	DirectX::XMFLOAT3 object1;
	DirectX::XMStoreFloat3(&object1, vec1);
	DirectX::XMFLOAT3 object2;
	DirectX::XMStoreFloat3(&object2, vec2);
	float distance = sqrt((object1.x - object2.x) * (object1.x - object2.x)
						+ (object1.y - object2.y) * (object1.y - object2.y)
						+ (object1.z - object2.z) * (object1.z - object2.z));
	return distance;
}


std::vector<std::string> CollisionEngine::TestCollision()
{	
	// move objects in a vector

	std::vector<GameObject*> gameobjects;
	std::vector<std::string> names;
	for (auto& it : m_gameObjects->GetGameObjects()) {
		GameObject* gameObject;

		gameObject = m_gameObjects->GetGameObjects().at(it.first);
		if (gameObject->GetCollisionSphere() != nullptr)
		{
			gameobjects.push_back(gameObject);
		}	
	}
	//test all objects against eachother
	for (int i = 0; i < gameobjects.size();i++) {

		//get the next GameObject the obj manager
		for (int j = i + 1; j < gameobjects.size(); j++)
		{
			float distance = CalculateDistance(gameobjects[i]->GetPositionVec(), gameobjects[j]->GetPositionVec());

			if (distance < gameobjects[i]->GetCollisionSphere()->GetRadius() || distance < gameobjects[j]->GetCollisionSphere()->GetRadius())
			{
				 names.push_back(gameobjects[i]->GetName());
				 names.push_back(gameobjects[j]->GetName());

				 return names;
			}
		}
	}
	return names;
}
