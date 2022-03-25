#include "modelmanager.h"

ModelManager::ModelManager()
{
	//m_model = 0;
	//m_texture = 0;
	//m_mesh = 0;
	m_device = 0;
	m_allModels.clear();
}

ModelManager::ModelManager(const ModelManager&)
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::SetDevice( ID3D11Device* deviceContext)
{
	m_device = deviceContext;
}

void ModelManager::Shutdown()
{
	for (auto& it : m_allModels) {
		Model model;

		model = m_allModels.at(it.first);

		model.m_mesh.Shutdown();
		model.m_texture.Shutdown();

	}
	m_allModels.clear();

}

void ModelManager::GetHandle(HWND handle)
{
	m_hwnd = handle;
}

void ModelManager::SetTexture(const WCHAR* texture)
{
	m_textLocation = texture;
}

void ModelManager::SetMesh(const char* meshLocation)
{
	m_meshFile = meshLocation;
}


void ModelManager::Set(string name)
{
	bool result;
	Model model;

	
	result = model.m_texture.Initialize(m_device, m_textLocation);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the texture.", L"Error", MB_OK);
	}

	result = model.m_mesh.Initialize(m_device, m_meshFile, &model.m_texture);


	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the model.", L"Error", MB_OK);
	}


	m_allModels.insert({ name, model });

}
