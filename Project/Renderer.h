#ifndef _Renderer_H_
#define _Renderer_H_

#include <d3d11.h>
#include <DirectXMath.h>

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&);
	~Renderer();

	
	bool Initialize(int, int, bool, HWND, bool, float, float); // (screenWidth, screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(DirectX::XMFLOAT4X4&);
	void GetWorldMatrix(DirectX::XMFLOAT4X4&);
	void GetOrthoMatrix(DirectX::XMFLOAT4X4&);

	void GetVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	DirectX::XMFLOAT4X4 m_projectionMatrix;
	DirectX::XMFLOAT4X4 m_worldMatrix;
	DirectX::XMFLOAT4X4 m_orthoMatrix;
};


#endif
