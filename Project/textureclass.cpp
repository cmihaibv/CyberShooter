////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"


TextureClass::TextureClass()
{
	m_texture = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device,const WCHAR* filename)
{
	HRESULT result;
	TexMetadata m_textMetaData;
	ScratchImage m_image;


	// Load the texture
	result = LoadFromDDSFile(filename, DDS_FLAGS_NONE, &m_textMetaData, m_image);
	if(FAILED(result))
	{
		return false;
	}

	result = CreateShaderResourceView(device, NULL,NULL, m_textMetaData, &m_texture);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}