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
		float tu = 0, tv = 0;
		float nx = 0, ny = 0, nz = 0;
	};

public:

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, const char*, TextureClass*);

	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	void SetTexture(TextureClass*);
	ID3D11ShaderResourceView* GetTexture();

	XMMATRIX& GetModelMatrix();

private:
	bool InitializeBuffers(ID3D11Device*);
	bool VertexBufferDesc(ID3D11Device*, int, DXVertexType*);
	bool IndexBufferDesc(ID3D11Device*, int, unsigned long*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	void ReleaseTexture();

	bool LoadObj(const char*);
	void ReleaseModel();

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	std::vector<NormalVertex> m_model;

	XMFLOAT3 m_position = XMFLOAT3(0, -2.0f, 300.0f);		// world position of the object
	XMFLOAT3 m_rotation = XMFLOAT3(0, 120, 0);				// world rotation of the object

	XMMATRIX m_modelView = XMMatrixIdentity();				// model matrix, set to identity by default
};

#endif