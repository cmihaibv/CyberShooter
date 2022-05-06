#pragma once

#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include <d3d11.h>
#include <fstream>
#include <unordered_map>
#include "modelclass.h"

using namespace std;


class ModelManager
{
public:
	ModelManager();
	ModelManager(const ModelManager&);
	~ModelManager();

	void SetD3DDevice(ID3D11Device*);

	/// <summary>
	/// File path define like:  L" filepath" 
	/// </summary>
	/// <param name=""> WCHAR filepath</param>
	/// <returns></returns>
	bool InitialiseModel(string, const char*);
	ModelClass* GetModel(string);

	void ReleaseModels();

protected:

	ID3D11Device* m_device;					// d3d handle to read & write
	std::unordered_map<std::string, ModelClass*> m_models;


private:
	string m_name;

};

#endif
