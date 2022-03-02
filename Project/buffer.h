#ifndef _BUFFER_H_
#define _BUFFER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: ColorShaderClass
////////////////////////////////////////////////////////////////////////////////
class Buffer
{
private:
	//Define the constant data used to comunicate with shaders
	struct VS_CONSTANT_BUFF_T
	{
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

public:
	Buffer();
	Buffer(const Buffer&);
	~Buffer();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, DirectX::XMFLOAT4X4, DirectX::XMFLOAT4X4, DirectX::XMFLOAT4X4);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*,const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND,const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, DirectX::XMFLOAT4X4, DirectX::XMFLOAT4X4, DirectX::XMFLOAT4X4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif