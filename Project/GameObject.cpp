#include "GameObject.h"

GameObject::GameObject()
{
	//m_modelView = XMMatrixTranslation(m_position.x, m_position.y, m_position.z) * XMMatrixRotationY(m_rotation.y);
	m_vecRight = XMVectorReplicateInt(0);
	m_device = 0;
	m_model = 0;
	m_texture = 0;
	m_vecForward = XMVectorReplicateInt(0);
	m_vecLeft = XMVectorReplicateInt(0);
	m_vecRight = XMVectorReplicateInt(0);
	m_vecBackward = XMVectorReplicateInt(0);


}

GameObject::GameObject(const GameObject& other)
{
	memcpy(this, &other, sizeof(GameObject));
}

GameObject::~GameObject()
{
}

void GameObject::SetD3DDevice(ID3D11Device* device)
{
	m_device = device;
}

void GameObject::SetName(string name)
{
	m_name = name;
}

string GameObject::GetName()
{
	return m_name;
}

bool GameObject::SetTexture(TextureClass* texture)
{

	m_texture = texture;
	return true;
}

bool GameObject::SetModel(ModelClass* model)
{
	m_model = model;
	m_model->SetTexture(m_texture);
	return true;
}

void GameObject::SetPosition(float xposition,float yposition, float zposition)
{
	m_position.x = xposition;
	m_position.y = yposition;
	m_position.z = zposition;
	m_posVec = XMLoadFloat3(&m_position);
	if (m_collisionsphere != nullptr)
	{
		m_collisionsphere->UpdatePosition(m_posVec);
	}
	UpdateModelMatrix();
}

void GameObject::SetRotation(float xrotation, float yrotation, float zrotation)
{
	m_rotation.x = xrotation;
	m_rotation.y = yrotation;
	m_rotation.z = zrotation;
	m_rotVec = XMLoadFloat3(&m_rotation);
	UpdateModelMatrix();
}

void GameObject::SetScale(float xscale, float yscale, float zscale)
{
	m_scale.x = xscale;
	m_scale.y = yscale;
	m_scale.z = zscale;
	m_scaleVec = XMLoadFloat3(&m_scale);
	UpdateModelMatrix();
}

void GameObject::UpdatePosition(XMVECTOR& pos)
{

	m_posVec += pos;
	XMStoreFloat3(&m_position, m_posVec);
	if (m_collisionsphere != nullptr)
	{
		m_collisionsphere->UpdatePosition(m_posVec);
	}
	
	UpdateModelMatrix();

}

void GameObject::UpdateRotation(XMVECTOR& rot)
{
	
	m_rotVec += rot;
	XMStoreFloat3(&m_rotation, m_rotVec);
	UpdateModelMatrix();
}

void GameObject::UpdateModelMatrix()
{
	// Translate and rotate the model
	this->m_modelView = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) * XMMatrixRotationRollPitchYaw(0, this->m_rotation.y, 0) * XMMatrixTranslation(this->m_position.x, this->m_position.y, this->m_position.z) ;

	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->m_rotation.y, 0.0f);

	m_vecForward = XMVector3TransformCoord(m_DefaultForwardVec, vecRotationMatrix);
	m_vecBackward = XMVector3TransformCoord(m_DefaultBackwardVec, vecRotationMatrix);
	m_vecLeft = XMVector3TransformCoord(m_DefaultLeftVec, vecRotationMatrix);
	m_vecRight = XMVector3TransformCoord(m_DefaultRightVec, vecRotationMatrix);

}

const XMVECTOR& GameObject::GetForwardVector()
{
	return m_vecForward;
}

const XMVECTOR& GameObject::GetRightVector()
{
	return m_vecRight;
}

const XMVECTOR& GameObject::GetBackwardVector()
{
	return m_vecBackward;
}

const XMVECTOR& GameObject::GetLeftVector()
{
	return m_vecLeft;
}

XMFLOAT3& GameObject::GetPosition()
{
	return m_position;
}

XMVECTOR& GameObject::GetPositionVec()
{
	return m_posVec;
}

XMVECTOR& GameObject::GetRotation()
{
	return m_rotVec;
}

XMMATRIX& GameObject::modelMatrix()
{
	return m_modelView;
}

void GameObject::SetCollisionSphere(CollisionSphere* collisionsphere)
{
	m_collisionsphere = collisionsphere;
}

CollisionSphere* GameObject::GetCollisionSphere()
{
	return m_collisionsphere;
}

void GameObject::UpdateCollision()
{
	m_collisionsphere->UpdatePosition(m_posVec);
}
void GameObject::Action()
{
}
void GameObject::Action(GameObject& gobj)
{

}
void GameObject::Action(GameObject* gobj)
{
}
bool GameObject::Alive()
{
	return true;
}
State GameObject::GetState()
{
	return m_state;
}
void GameObject::ReleaseObject()
{

}

void GameObject::SetTag(string tag)
{
	m_tag = tag;
}

void GameObject::AddCollidable(string tag)
{
	collideList.push_back(tag);
}

vector<string> GameObject::GetCollidable()
{
	return collideList;
}
