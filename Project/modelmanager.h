#pragma once

#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include <unordered_map>
#include <string>
#include "textureclass.h"
#include "modelclass.h"



class ModelManager {
private:
	struct Model
	{
		TextureClass m_texture;
		ModelClass m_mesh;
	};

	struct Object
	{
		ModelClass* m_model;
		XMMATRIX position;
	};



public:
	ModelManager();
	ModelManager(const ModelManager&);
	~ModelManager();

	void Initialise();
	void SetTexture();
	void SetMesh();


private:
	Model* m_model;
	std::unordered_map<std::string, Model*> allModels;


};



#endif