#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::TextureManager(const TextureManager&)
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::SetD3DDevice(ID3D11Device* device)
{
	m_device = device;
}

bool TextureManager::InitialiseTexture(string name ,const WCHAR* texLocation)
{
	bool result;

	TextureClass* texture = new TextureClass;

	result = texture->Initialize(m_device, texLocation);	// replace hardcoded location with texLocation !!!!!! L"../Project/data/guntex.dds"
	if (!result)
	{
		//MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);

		return -1;
	}

	m_textures.insert({ name, texture });

	return true;
}

TextureClass* TextureManager::GetTexture(string texturename)
{
	return m_textures.at(texturename);
}

void TextureManager::ReleaseTextures()
{
	for (auto& it : m_textures) {
		TextureClass* texture;

		texture = m_textures.at(it.first);

		//Release texture and delete pointer
		if (texture)
		{
			texture->Shutdown();
			delete texture;
			texture = 0;
		}

	}
	m_textures.clear();
}
