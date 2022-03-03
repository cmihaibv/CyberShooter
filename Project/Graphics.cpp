
#include "Graphics.h"


GraphicsClass::GraphicsClass()
{
	m_D3DXRenderer = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenHeight, int screenWidth, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3DXRenderer = new Renderer;
	if (!m_D3DXRenderer)
	{
		return false;
	}
	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	//vs -ps -etc.
		// Create the model object.
	m_Model = new Object;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3DXRenderer->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FALSE, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	const char* a = "../Debug/data/cube.txt";
	result = m_Model->Initialize(m_D3DXRenderer->GetDevice(), a);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object22.", L"Error", MB_OK);
		return false;
	}

	m_ColorShader = new Buffer;
	if (!m_ColorShader)
	{
		return false;
	}
	result = m_ColorShader->Initialize(m_D3DXRenderer->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3DXRenderer)
	{
		m_D3DXRenderer->Shutdown();
		delete m_D3DXRenderer;
		m_D3DXRenderer = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)DirectX::XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}


	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{

	DirectX::XMFLOAT4X4 worldMatrix, projectionsMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;

	bool result;
	// Clear the buffers to begin the scene.
	m_D3DXRenderer->BeginScene(1.0f, 1.0f, 0.0f, 1.0f);

	m_Camera->Render();


	m_Camera->GetViewMatrix(viewMatrix);
	m_D3DXRenderer->GetWorldMatrix(worldMatrix);
	m_D3DXRenderer->GetProjectionMatrix(projectionsMatrix);

	m_Model->Render(m_D3DXRenderer->GetDeviceContext());

	result = m_ColorShader->Render(m_D3DXRenderer->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionsMatrix);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3DXRenderer->EndScene();

	return true;
}