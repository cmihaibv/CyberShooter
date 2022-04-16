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

	void InitialiseProjection(float, float, float, float);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void UpdatePosition(XMVECTOR& pos);
	void UpdatePosition(float, float, float);

	void UpdateRotation(XMVECTOR& rot);
	void UpdateRotation(float, float, float);
	

	void UpdateCamera();
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	XMMATRIX& GetViewMatrix() ;
	XMMATRIX& GetProjectionMatrix();

	XMVECTOR GetPosition();
	XMVECTOR GetRotation();

	//////////
	//beta
	const XMVECTOR& GetForwardVector();
	const XMVECTOR& GetRightVector();
	const XMVECTOR& GetBackwardVector();
	const XMVECTOR& GetLeftVector();




private:

	float m_yaw = 0.f				//	camera orientation
		, m_pitch = 0.5f			//
		, m_roll = 0.f;				//

	float	m_screenWidth,			//	screen width px
			m_screenHeight,			//	screen height px
			m_FOV = 90,					//	fov in stored in degree's
			m_screenNear,			//	near plane on the camera
			m_screenDepth;			//	far plane on the camera

	XMFLOAT3 m_pos;
	XMFLOAT3 m_rot;

	XMVECTOR m_vEyePosition = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);	//	position of the camera in the world
	XMVECTOR m_rotVector = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		//	rotation of the camera

	XMVECTOR m_DefaultForwardVec = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR m_DefaultUpVec = XMVectorSet(0.0f, 1.0f, 1.0f, 0.0f);


	XMMATRIX m_modelMatrix = XMMatrixIdentity();		//	model matrix
	XMMATRIX m_viewMatrix = XMMatrixIdentity();			//	view matrix set as identity
	XMMATRIX m_projectionMatrix = XMMatrixIdentity();	//	projection matrix set as identity

	const XMVECTOR m_DefaultBackwardVec = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);	// move in the direction relative to the rotation
	const XMVECTOR m_DefaultLeftVec = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);		//
	const XMVECTOR m_DefaultRightVec = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);		//

	XMVECTOR m_vecForward;		// move in the direction relative to the rotation
	XMVECTOR m_vecLeft;			//
	XMVECTOR m_vecRight;		//
	XMVECTOR m_vecBackward;		//
};

#endif