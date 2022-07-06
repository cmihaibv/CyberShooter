#include "ModelManager.h"

ModelManager::ModelManager()
{
}

ModelManager::ModelManager(const ModelManager&)
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::SetD3DDevice(ID3D11Device* device)
{
	m_device = device;
}

bool ModelManager::InitialiseModel(string name, const char* modelLocation)
{
	bool result;

	ModelClass* model = new ModelClass;
	if (!model)
	{
		return false;
	}

	result = model->Initialize(m_device, modelLocation);		// replace hardcoded location with texLocation !!!!!! "../Project/data/mp5k.obj"
	if (!result)
	{
		//MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_models.insert({ name, model });
	return true;
}

ModelClass* ModelManager::GetModel(string modelname)
{
	return m_models.at(modelname);
}

void ModelManager::ReleaseModels()
{
	for (auto& it : m_models) {
		ModelClass* model;

		model = m_models.at(it.first);

		//Release texture and delete pointer
		if (model)
		{
			model->Shutdown();
			delete model;
			model = 0;
		}

	}
	m_models.clear();
}
