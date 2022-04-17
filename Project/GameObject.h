#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include "modelclass.h"


using namespace std;
using namespace DirectX;


#include "textureclass.h"

class GameObject
{
public:
	GameObject();
	GameObject(const GameObject&);
	~GameObject();

	void SetD3DDevice(ID3D11Device*);

	/// <summary>
	/// File path define like:  L" filepath" 
	/// </summary>
	/// <param name=""> WCHAR filepath</param>
	/// <returns></returns>
	bool SetTexture(const WCHAR*);
	bool SetModel(const char*);

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


	//beta
	XMMATRIX& modelMatrix();
	//
	void ReleaseObject();

	TextureClass* m_texture;
	ModelClass* m_model;
private:

	ID3D11Device* m_device;					// d3d handle to read & write
	bool m_isUpdated = false;				// is updated?

	XMVECTOR m_posVec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		//	position of the object in the world
	XMVECTOR m_rotVec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		//	rotation of the object
	XMVECTOR m_scaleVec = XMVectorSet(1.0f,1.0f, 1.0f, 0.0f);

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