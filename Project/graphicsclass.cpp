#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FALSE, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_gameObjectManager = new GameObjectManager;
	if (!m_gameObjectManager)
	{
		return false;
	}

	//// Create the model object.
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}

	//m_Texture = new TextureClass;
	//if (!m_Texture)
	//{
	//	return false;
	//}

	//result = m_Texture->Initialize(m_D3D->GetDevice(), L"../Project/data/guntex.dds");
	//if (!result)
	//{
	//	return false;
	//}

	//// Initialize the model object.
	//result = m_Model->Initialize(m_D3D->GetDevice(), "../Project/data/mp5k.obj", m_Texture);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the game object manager.
	if (m_gameObjectManager)
	{
		m_gameObjectManager->Shutdown();
		delete m_gameObjectManager;
		m_gameObjectManager = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

ID3D11Device* GraphicsClass::GetDevice()
{
	return m_D3D->GetDevice();
}

void GraphicsClass::SetCamera(CameraClass* cam)
{
	m_Camera = cam;
}

void GraphicsClass::InitialiseGameObjects(GameObjectManager* gameobjmgr)
{
	m_gameObjectManager = gameobjmgr;
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Update the view matrix based on the camera's position.
	m_Camera->UpdateCamera();

	// Render game objects	
	viewMatrix = m_Camera->GetViewMatrix();
	projectionMatrix = m_Camera->GetProjectionMatrix();

	

	for (auto& it : m_gameObjectManager->GetGameObjects())
	{
		GameObject* gobj;

		gobj = m_gameObjectManager->GetGameObjects().at(it.first);

		gobj->m_model->Render(m_D3D->GetDeviceContext());

		worldMatrix = gobj->modelMatrix();



		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), gobj->m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			gobj->m_model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
		if (!result)
		{
			return false;
		}
	}


	
	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	////m_gameobj->m_model->Render(m_D3D->GetDeviceContext());

	// Get the world, view, and projection matrices from the camera and objects.
	//worldMatrix = m_gameobj->modelMatrix();
	//viewMatrix = m_Camera->GetViewMatrix();
	//projectionMatrix = m_Camera->GetProjectionMatrix();


	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_gameobj->m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_gameobj->m_model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	/*GameObject* gobj;

	gobj = m_gameObjectManager->GetGameObject("gun");

	worldMatrix = XMMatrixRotationY(115)* XMMatrixTranslation(13.f, 3.f, 130.f) ;*/

	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//if (!result)
	//{
	//	return false;
	//}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}