#include "modelmanager.h"
#include "modelclass.h"

ModelManager::ModelManager()
{
	m_model = 0;
	allModels.clear();
}

ModelManager::ModelManager(const ModelManager&)
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::SetTexture()
{
}

void ModelManager::SetMesh()
{
}

void ModelManager::Initialise()
{
	allModels.insert({ "quote", m_model });
}
