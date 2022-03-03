#include "Camera.h"


CameraClass::CameraClass()
{
	this->m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->m_posVector = DirectX::XMLoadFloat3(&this->m_position);
	this->m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->m_rotVector = DirectX::XMLoadFloat3(&this->m_rotation);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPositionVec(const DirectX::XMVECTOR& pos)
{

}

void CameraClass::SetPosition(float x, float y, float z)
{
	this->m_position.x = x;
	this->m_position.y = y;
	this->m_position.z = z;
	this->m_posVector = DirectX::XMLoadFloat3(&this->m_position);

	return;
}


void CameraClass::SetRotationVec(const DirectX::XMVECTOR& pos)
{
}

void CameraClass::SetRotation(float x, float y, float z)
{
	this->m_rotation.x = x;
	this->m_rotation.y = y;
	this->m_rotation.z = z;
	this->m_posVector = DirectX::XMLoadFloat3(&this->m_rotation);

	return;
}


DirectX::XMVECTOR CameraClass::GetPositionVec()
{
	return this->m_posVector;
}

DirectX::XMFLOAT3 CameraClass::GetPosition()
{
	return DirectX::XMFLOAT3(m_position.x, m_position.y, m_position.z);
}

DirectX::XMVECTOR CameraClass::GetRotationVec()
{
	return this->m_rotVector;
}


DirectX::XMFLOAT3 CameraClass::GetRotation()
{
	return DirectX::XMFLOAT3(m_rotation.x, m_rotation.y, m_rotation.z);
}


void CameraClass::Render()
{
	DirectX::XMFLOAT3 up, position, lookAt;
	float yaw, pitch, roll;
	DirectX::XMFLOAT4X4 rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = this->m_position.x;
	position.y = this->m_position.y;
	position.z = this->m_position.z;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	DirectX::XMMATRIX rotMatrix;
	rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw);
	DirectX::XMStoreFloat4x4(&rotationMatrix, rotMatrix);


	
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	DirectX::XMVECTOR lookAtVec, upVec;
	lookAtVec = DirectX::XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotMatrix);
	upVec = DirectX::XMVector3TransformCoord(XMLoadFloat3(&up), rotMatrix);
	DirectX::XMStoreFloat3(&lookAt, lookAtVec);
	DirectX::XMStoreFloat3(&up, upVec);


	// Translate the rotated camera position to the location of the viewer.
	lookAtVec += this->m_posVector;

	// Finally create the view matrix from the three updated vectors.
	XMStoreFloat4x4(&m_viewMatrix, XMMatrixLookAtLH(XMLoadFloat3(&position), lookAtVec, upVec));
	return;
}


void CameraClass::GetViewMatrix(DirectX::XMFLOAT4X4& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}