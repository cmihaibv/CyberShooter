#include "Enemy.h"

Enemy::Enemy()
{
	m_state = State::PATROL;
	m_vecRight = XMVectorReplicateInt(0);
	m_device = 0;
	m_model = 0;
	m_texture = 0;
	m_vecForward = XMVectorReplicateInt(0);
	m_vecLeft = XMVectorReplicateInt(0);
	m_vecRight = XMVectorReplicateInt(0);
	m_vecBackward = XMVectorReplicateInt(0);
	m_target = nullptr;
}
void Enemy::Action()
{
	// chase player 
	//update forward vector
	XMFLOAT3 newVector = { m_target->GetPosition().x - this->GetPosition().x,
		0,
		m_target->GetPosition().z - this->GetPosition().z };

	XMVECTOR newVecForward = XMLoadFloat3(&newVector);
	newVecForward = XMVector3Normalize(newVecForward);
	if (!XMVector3Equal(m_vecForward,newVecForward))
	{
		XMVECTOR rot = XMVector3AngleBetweenVectors(m_DefaultForwardVec, newVecForward);
		if ((XMVectorGetX(newVecForward) < 0 && XMVectorGetZ(newVecForward) < 0) || XMVectorGetX(newVecForward) < 0)
			rot = XMVectorSet(6.28319-XMVectorGetX(rot), 6.28319- XMVectorGetY(rot), 6.28319- XMVectorGetZ(rot), 6.28319- XMVectorGetW(rot));

		this->UpdateRotation(rot);
		m_vecForward = newVecForward;
	}


	//move closer 
	float distance = sqrt((m_position.x - m_target->GetPosition().x) * (m_position.x - m_target->GetPosition().x)
		+ (m_position.y - m_target->GetPosition().y) * (m_position.y - m_target->GetPosition().y)
		+ (m_position.z - m_target->GetPosition().z) * (m_position.z - m_target->GetPosition().z));

	if (distance < m_detectionDistance && distance >m_attackDistance)
	{
		XMVECTOR newVec = m_vecForward * 0.05;
		UpdatePosition(newVec);
	}
}

void Enemy::Action(GameObject& obj)
{
	m_target = &obj;

	float distance = sqrt((m_position.x - m_target->GetPosition().x) * (m_position.x - m_target->GetPosition().x)
						+ (m_position.y - m_target->GetPosition().y) * (m_position.y - m_target->GetPosition().y)
						+ (m_position.z - m_target->GetPosition().z) * (m_position.z - m_target->GetPosition().z));

	//define a state

	
	if (distance < m_attackDistance)
	{
		m_state = State::SHOOT;
	}
	if (distance < m_detectionDistance)
	{
		m_state = State::CHASE;
	}
	if (distance > m_detectionDistance)
	{
		m_state = State::PATROL;
		//m_target = nullptr;
	}
	Action();
}		
void Enemy::Action(GameObject* obj)
{
	m_target = obj;

	float distance = sqrt((m_position.x - m_target->GetPosition().x) * (m_position.x - m_target->GetPosition().x)
		+ (m_position.y - m_target->GetPosition().y) * (m_position.y - m_target->GetPosition().y)
		+ (m_position.z - m_target->GetPosition().z) * (m_position.z - m_target->GetPosition().z));

	//define a state
	if (distance < m_detectionDistance)
	{
		m_state = State::CHASE;
	}
	if (distance < m_attackDistance)
	{
		m_state = State::SHOOT;
	}
	if (distance > m_detectionDistance)
	{
		m_state = State::PATROL;
		//m_target = nullptr;
	}
	Action();
}

State Enemy::GetState()
{
	return m_state;
}
