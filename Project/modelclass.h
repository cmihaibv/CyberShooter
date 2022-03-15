#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace std;
using namespace DirectX;


#include "textureclass.h"



class ModelClass
{
private:
	struct DXVertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct NormalVertex
	{
		float x, y, z;
		float tu = 0 , tv = 0;
		float nx = 0, ny = 0, nz = 0;
	};

public:

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, const char*, const WCHAR*,TextureClass*);
	
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	void SetTexture(TextureClass*);
	ID3D11ShaderResourceView* GetTexture();


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*,const WCHAR*);
	void ReleaseTexture();

	bool LoadModel(const char*);
	bool LoadObj(const char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	NormalVertex* m_model;
};

#endif