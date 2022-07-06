#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_vEyePosition= XMLoadFloat3(&m_pos);
	m_rotVector = XMLoadFloat3(&m_rot);
}


CameraClass::CameraClass(const CameraClass& other)
{

}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_pos = XMFLOAT3(x, y, z);
	m_vEyePosition = XMLoadFloat3(&m_pos);
	UpdateViewMatrix();
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rot = XMFLOAT3(x, y, z);
	m_rotVector = XMLoadFloat3(&m_rot);
	UpdateViewMatrix();
	return;
}

void CameraClass::UpdatePosition(XMVECTOR& pos)
{
	m_vEyePosition += pos;
	XMStoreFloat3(&m_pos, pos);
	UpdateViewMatrix();
}

void CameraClass::UpdatePosition(float x, float y, float z)
{
	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;
	m_vEyePosition = XMLoadFloat3(&m_pos);
	UpdateViewMatrix();
}

void CameraClass::UpdateRotation(XMVECTOR& rot)
{
	m_rotVector += rot;
	XMStoreFloat3(&m_rot, rot);
	UpdateViewMatrix();
}

void CameraClass::UpdateRotation(float x, float y, float z)
{
	m_rot.x += x;
	m_rot.y += y;
	m_rot.z += z;
	m_rotVector = XMLoadFloat3(&m_rot);
	UpdateViewMatrix();
}

void CameraClass::InitialiseProjection(float screenW, float screenH, float sNear, float sDepth)
{
	m_screenWidth = screenW;
	m_screenHeight = screenH;
	m_screenNear = sNear;
	m_screenDepth = sDepth;
	UpdateProjectionMatrix();
}


XMVECTOR CameraClass::GetPosition()
{
	return m_vEyePosition;
}


XMVECTOR CameraClass::GetRotation()
{
	return m_rotVector;
}

const XMVECTOR& CameraClass::GetForwardVector()
{
	return m_vecForward;
}

const XMVECTOR& CameraClass::GetRightVector()
{
	return m_vecRight;
}

const XMVECTOR& CameraClass::GetBackwardVector()
{
	return m_vecBackward;
}

const XMVECTOR& CameraClass::GetLeftVector()
{
	return m_vecLeft;
}

void CameraClass::UpdateCamera()
{
	UpdateViewMatrix();

	UpdateProjectionMatrix();
}

void CameraClass::UpdateViewMatrix()
{

	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);

	//Calculate unit vector of cam target based off camera forward value transformed by cam rotation matrix
	XMVECTOR camTarget = XMVector3TransformCoord(m_DefaultForwardVec, camRotationMatrix);

	//Adjust cam target to be offset by the camera's current position
	camTarget += m_vEyePosition;

	//Calculate up direction based on current rotation
	XMVECTOR upDir = XMVector3TransformCoord(m_DefaultUpVec, camRotationMatrix);

	//Rebuild view matrix
	m_viewMatrix = XMMatrixLookAtLH(m_vEyePosition, camTarget, upDir);

	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->m_rot.y, 0.0f);
	m_vecForward = XMVector3TransformCoord(m_DefaultForwardVec, vecRotationMatrix);
	m_vecBackward = XMVector3TransformCoord(m_DefaultBackwardVec, vecRotationMatrix);
	m_vecLeft = XMVector3TransformCoord(m_DefaultLeftVec, vecRotationMatrix);
	m_vecRight = XMVector3TransformCoord(m_DefaultRightVec, vecRotationMatrix);
}


void CameraClass::UpdateProjectionMatrix()
{
	float screenAspect = static_cast<float>(m_screenWidth) / static_cast<float>(m_screenHeight);

	// Create the projection matrix for 3D rendering. 
	m_projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(90), screenAspect, m_screenNear, m_screenDepth);
	
	return;
}

XMMATRIX& CameraClass::GetViewMatrix()
{
	return m_viewMatrix;
}

XMMATRIX& CameraClass::GetProjectionMatrix()
{
	return m_projectionMatrix;
}


