#pragma once

#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <d3d11.h>
#include <fstream>
#include <unordered_map>
#include "textureclass.h"

using namespace std;


#include "textureclass.h"

class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager&);
	~TextureManager();

	void SetD3DDevice(ID3D11Device*);

	/// <summary>
	/// File path define like:  L" filepath" 
	/// </summary>
	/// <param name=""> WCHAR filepath</param>
	/// <returns></returns>
	bool InitialiseTexture(string,const WCHAR*);
	TextureClass* GetTexture(string);

	void ReleaseTextures();

protected:

	ID3D11Device* m_device;					// d3d handle to read & write
	std::unordered_map<std::string,TextureClass*> m_textures;


private:
	string m_name;

};

#endif
