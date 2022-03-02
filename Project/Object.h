#ifndef _Object_H_
#define _Object_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace std;

class Object
{
private:
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float r, g, b, a;
		float nx, ny, nz;
	};

public:
	Object();
	Object(const Object&);
	~Object();

	bool Initialize(ID3D11Device*, const char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	char modelFilename;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadModel(const char*);
	void ReleaseModel();
	

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ModelType* m_model;
	
};

#endif