#include "CollisionSphere.h"


CollisionSphere::CollisionSphere()
{
}

CollisionSphere::CollisionSphere(const CollisionSphere&)
{
}

CollisionSphere::~CollisionSphere()
{

}


void CollisionSphere::SetRadius(float radius)
{
	m_radius = radius;
}

float CollisionSphere::GetRadius()
{
	return m_radius;
}

void CollisionSphere::UpdatePosition(XMVECTOR& pos)
{
	m_posVec = pos;
	XMStoreFloat3(&m_position, m_posVec);
	UpdateModelMatrix();
}

void CollisionSphere::UpdateRotation(XMVECTOR&)
{
}


void CollisionSphere::SetPosition(float xposition, float yposition, float zposition)
{
	m_position.x = xposition;
	m_position.y = yposition;
	m_position.z = zposition;
	m_posVec = XMLoadFloat3(&m_position);
	UpdateModelMatrix();
}

void CollisionSphere::SetRotation(float, float, float)
{
}


void CollisionSphere::SetScale(float xscale, float yscale, float zscale)
{
	m_scale.x = xscale;
	m_scale.y = yscale;
	m_scale.z = zscale;
	m_scaleVec = XMLoadFloat3(&m_scale);
	UpdateModelMatrix();
}

void CollisionSphere::UpdateModelMatrix()
{
	// Translate and rotate the model
	this->m_modelView = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) * XMMatrixRotationRollPitchYaw(this->m_rotation.x, this->m_rotation.y, this->m_rotation.z) * XMMatrixTranslation(this->m_position.x, this->m_position.y, this->m_position.z);

	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->m_rotation.y, 0.0f);

	m_vecForward = XMVector3TransformCoord(m_DefaultForwardVec, vecRotationMatrix);
	m_vecBackward = XMVector3TransformCoord(m_DefaultBackwardVec, vecRotationMatrix);
	m_vecLeft = XMVector3TransformCoord(m_DefaultLeftVec, vecRotationMatrix);
	m_vecRight = XMVector3TransformCoord(m_DefaultRightVec, vecRotationMatrix);

}

const XMVECTOR& CollisionSphere::GetForwardVector()
{
	return m_vecForward;
}

const XMVECTOR& CollisionSphere::GetRightVector()
{
	return m_vecRight;
}

const XMVECTOR& CollisionSphere::GetBackwardVector()
{
	return m_vecBackward;
}

const XMVECTOR& CollisionSphere::GetLeftVector()
{
	return m_vecLeft;
}

XMFLOAT3& CollisionSphere::GetPosition()
{
	return m_position;
}

XMVECTOR& CollisionSphere::GetPositionVec()
{
	return m_posVec;
}

XMMATRIX& CollisionSphere::modelMatrix()
{
	return m_modelView;
}