#pragma once

#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include <unordered_map>
#include <string>
#include "modelclass.h"
#include "textureclass.h"
#include "d3dclass.h"





class ModelManager {
private:
	struct Model
	{
		TextureClass m_texture;
		ModelClass m_mesh;
	};

	struct GameObject
	{
		Model* m_model;
		XMMATRIX position;
	};



public:
	ModelManager();
	ModelManager(const ModelManager&);
	~ModelManager();

	void Set(string);
	void SetDevice(ID3D11Device*);
	void Shutdown();

	void GetHandle(HWND);
	void SetTexture(const WCHAR*);
	void SetMesh(const char*);


private:
	//ModelClass* m_mesh;
	//Model* m_model;
	//TextureClass* m_texture;
	std::unordered_map<std::string, Model> m_allModels;

	const WCHAR* m_textLocation;
	const char* m_meshFile;

	ID3D11Device* m_device;
	HWND m_hwnd;

};



#endif