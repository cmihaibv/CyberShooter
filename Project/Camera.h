////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPositionVec(const DirectX::XMVECTOR &pos);
	void SetPosition(float, float, float);

	void SetRotationVec(const DirectX::XMVECTOR& pos);
	void SetRotation(float, float, float);

	DirectX::XMVECTOR GetPositionVec();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMVECTOR GetRotationVec();
	DirectX::XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(DirectX::XMFLOAT4X4&);

private:
	DirectX::XMVECTOR m_posVector;
	DirectX::XMVECTOR m_rotVector;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT4X4 m_viewMatrix;
	DirectX::XMFLOAT4X4 m_projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};

#endif