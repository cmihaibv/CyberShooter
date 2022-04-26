#pragma once

#ifndef _COLLISIONSPHERE_H_
#define _COLLISIONSPHERE_H_

#include <DirectXMath.h>
#include "unordered_map"

using namespace DirectX;

class CollisionSphere
{
public:
	CollisionSphere();
	CollisionSphere(const CollisionSphere&);
	~CollisionSphere();

	void SetRadius(float);
	float GetRadius();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetScale(float, float, float);

	void UpdatePosition(XMVECTOR&);
	void UpdateRotation(XMVECTOR&);
	void UpdateModelMatrix();

	const XMVECTOR& GetForwardVector();
	const XMVECTOR& GetRightVector();
	const XMVECTOR& GetBackwardVector();
	const XMVECTOR& GetLeftVector();

	XMFLOAT3& GetPosition();
	XMVECTOR& GetPositionVec();
	XMMATRIX& modelMatrix();

private:
	float m_radius =0.0;


	XMVECTOR m_posVec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		//	position of the object in the world
	XMVECTOR m_rotVec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		//	rotation of the object
	XMVECTOR m_scaleVec = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);

	XMVECTOR m_vecForward;		// move in the direction relative to the position&rotation
	XMVECTOR m_vecLeft;			//
	XMVECTOR m_vecRight;		//
	XMVECTOR m_vecBackward;		//


	XMFLOAT3 m_position = XMFLOAT3(0, 0, 0);		// world position of the object
	XMFLOAT3 m_rotation = XMFLOAT3(0, 0, 0);		// world rotation of the object
	XMFLOAT3 m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);	// scale 

	XMMATRIX m_modelView = XMMatrixIdentity();				// model matrix, set to identity by default

	//Default Vectors

	const XMVECTOR m_DefaultForwardVec = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);	//	move object relative to his position&rotation
	const XMVECTOR m_DefaultUpVec = XMVectorSet(0.0f, 1.0f, 1.0f, 0.0f);		//
	const XMVECTOR m_DefaultBackwardVec = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);	// 
	const XMVECTOR m_DefaultLeftVec = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);		//
	const XMVECTOR m_DefaultRightVec = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);		//

};
#endif