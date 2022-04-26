#include "systemclass.h"


SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_camera = 0;

}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;


	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	timer.Start();

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}

	m_gameObjectManager = new GameObjectManager;
	if (!m_gameObjectManager)
	{
		return false;
	}


	// Create the camera object.
	m_camera = new CameraClass;
	if (!m_camera)
	{
		return false;
	}

	m_collisionEngine = new CollisionEngine;
	if (!m_collisionEngine)
	{
		return false;
	}


	m_camera->InitialiseProjection(screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	// Set the initial position of the camera.
	m_camera->SetPosition(0.0f, 0.0f, -3.0f);

	// Send camera in Graphics
	m_Graphics->SetCamera(m_camera);

	InitialiseObjects();



	
	return true;
}


void SystemClass::InitialiseObjects()
{
	
	//for (int i = 0; i < 3;i++)
	//{
	//	GameObject* obj = new GameObject;

	//	obj->SetD3DDevice(m_Graphics->GetDevice());
	//	obj->SetTexture(L"../Project/data/guntex.dds");
	//	obj->SetModel("../Project/data/mp5k.obj");
	//	obj->SetPosition(0, -2.0f, 100.f*i);
	//	obj->SetRotation(0, 120.f, 0);
	//	m_Graphics->InitialiseGameObject(obj, std::to_string(i));

	//}
	//GameObject* obj = new GameObject;
	//obj->SetD3DDevice(m_Graphics->GetDevice());
	//obj->SetTexture(L"../Project/data/guntex.dds");
	//obj->SetModel("../Project/data/mp5k.obj");
	//obj->SetPosition(0, -2.0f, 200.f);
	//obj->SetRotation(0, 120.f, 0);
	//m_Graphics->InitialiseGameObject(obj, "gun2");


	GameObject* map = new GameObject;
	map->SetName("map");
	map->SetD3DDevice(m_Graphics->GetDevice());
	map->SetTexture(L"../Project/data/maptex.dds");
	map->SetModel("../Project/data/map.obj");
	map->SetPosition(0, -2.0f, 0.f);
	map->SetRotation(0, 120.f, 0);
	m_gameObjectManager->AddGameObject(map, map->GetName());

	
	GameObject* gun = new GameObject;
	gun->SetName("gun");
	gun->SetD3DDevice(m_Graphics->GetDevice());
	gun->SetTexture(L"../Project/data/UMP_lambert1_BaseColor.dds");
	gun->SetModel("../Project/data/UMP.obj");
	gun->SetPosition(XMVectorGetX(m_camera->GetForwardVector()), -1.0, XMVectorGetZ(m_camera->GetPosition()));
	gun->SetRotation(XMVectorGetX(m_camera->GetRotation()), XMVectorGetY(m_camera->GetRotation()), XMVectorGetZ(m_camera->GetRotation()));
	gun->SetScale(0.1f, 0.1f, 0.1f);
	m_gameObjectManager->AddGameObject(gun, gun->GetName());

	////////////GameObj with sphere
	////////////
	GameObject* testobj = new GameObject;
	testobj->SetName("testobj");
	testobj->SetD3DDevice(m_Graphics->GetDevice());
	testobj->SetTexture(L"../Project/data/UMP_lambert1_BaseColor.dds");
	testobj->SetModel("../Project/data/UMP.obj");
	testobj->SetPosition(3,1, 5);
	testobj->SetRotation(0, 1, 2);
	testobj->SetScale(0.1f, 0.1f, 0.1f);
	
	CollisionSphere* colsp = new CollisionSphere;
	colsp->UpdatePosition(testobj->GetPositionVec());
	colsp->SetRadius(1.0f);
	testobj->SetCollisionSphere(colsp);
	m_gameObjectManager->AddGameObject(testobj, testobj->GetName());

	GameObject* testobj2 = new GameObject;
	testobj2->SetName("testobj2");
	testobj2->SetD3DDevice(m_Graphics->GetDevice());
	testobj2->SetTexture(L"../Project/data/UMP_lambert1_BaseColor.dds");
	testobj2->SetModel("../Project/data/UMP.obj");
	testobj2->SetPosition(2.5, 1, 5);
	testobj2->SetRotation(0, 1, 2);
	testobj2->SetScale(0.1f, 0.1f, 0.1f);

	CollisionSphere* colsp2 = new CollisionSphere;
	colsp2->UpdatePosition(testobj->GetPositionVec());
	colsp2->SetRadius(1.0f);
	testobj2->SetCollisionSphere(colsp2);
	m_gameObjectManager->AddGameObject(testobj2, testobj2->GetName());

	m_collisionEngine->SetGameObjectManager(m_gameObjectManager);

	m_Graphics->GetGameObjectManager(m_gameObjectManager);

}


void SystemClass::Shutdown()
{
	// Release the camera object.
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}
	// Release the graphics object.
	if (m_gameObjectManager)
	{
		m_gameObjectManager->Shutdown();
		delete m_gameObjectManager;
		m_gameObjectManager = 0;
	}

	if (m_collisionEngine)
	{
		delete m_collisionEngine;
		m_collisionEngine = 0;
	}


	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

	}

	return;
}

void MoveCharacter(CameraClass* camera, GameObjectManager* gamemgr,InputClass* input)
{
	float cameraVel = 0.1f;

	//Store pointer of the gameobject into a variable
	GameObject* gameobj = gamemgr->GetGameObject("gun");

	if (input->IsKeyDown(0x28)) // Move camera and weapon back
	{
		XMVECTOR moveBack = camera->GetBackwardVector() * cameraVel;

		camera->UpdatePosition(moveBack);
		moveBack = gameobj->GetBackwardVector() * cameraVel;
		gameobj->UpdatePosition(moveBack);
	}
	if (input->IsKeyDown(0x26)) // Move camera and weapon forward
	{
		XMVECTOR moveForward = camera->GetForwardVector() * cameraVel;
		camera->UpdatePosition(moveForward);

		moveForward = gameobj->GetForwardVector() * cameraVel;
		gameobj->UpdatePosition(moveForward);
	}
	if (input->IsKeyDown(0x25)) // Rotate camera 
	{
		camera->UpdateRotation(0, -cameraVel, 0); // Yaw
	}
	if (input->IsKeyDown(0x27)) // rotate camera
	{
		camera->UpdateRotation(0, +cameraVel, 0); //Yaw
	}

	//Rotate weapon
	gameobj->SetRotation(XMVectorGetX(camera->GetRotation()), XMVectorGetY(camera->GetRotation()), XMVectorGetZ(camera->GetRotation()));
}

bool SystemClass::UpdateDrawGamePlay()
{
	bool result;
	
	MoveCharacter(m_camera,m_gameObjectManager,m_Input);

	//Test collision between objects

	std::vector<string> collObjNames = m_collisionEngine->TestCollision();
	
	if (collObjNames.size() != 0)
	{
		for (int i = 0;i < collObjNames.size();i++)
		{
			std::string name = collObjNames[i];
			if (collObjNames.size() >0 )
			{	
				m_gameObjectManager->RemoveGameObject(name);
			}
		}
	}


	result = m_Graphics->Frame();
	return result;
}

bool SystemClass::Frame()
{
	float dt = (float)timer.GetMilisecondsElapsed();
	timer.Restart();

	bool result;


	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	switch (mode)
	{
	case Gamedata::GameState::MAINMENU:
		// Do the frame processing for the graphics object.
		result = UpdateDrawGamePlay();	
		if (!result)
		{
			return false;
		}
		return true;
		break;
	case Gamedata::GameState::SCORES:
		break;
	case Gamedata::GameState::PLAY:
		break;
	case Gamedata::GameState::LOST:
		break;
	case Gamedata::GameState::WON:
		break;
	}


}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;                       // handle to device context 
	RECT rcClient;                 // client area rectangle 
	POINT ptClientUL;              // client upper left corner 
	POINT ptClientLR;              // client lower right corner 
	static POINTS ptsBegin;        // beginning point 
	static POINTS ptsEnd;          // new endpoint 
	static POINTS ptsPrevEnd;      // previous endpoint 
	static BOOL fPrevLine = FALSE; // previous line flag 


	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		///////////
		///////////
		//Mouse Messages
		case WM_LBUTTONDOWN:
		{
			// Capture mouse input. 

			SetCapture(hwnd);

			// Retrieve the screen coordinates of the client area, 
			// and convert them into client coordinates. 

			GetClientRect(hwnd, &rcClient);
			ptClientUL.x = rcClient.left;
			ptClientUL.y = rcClient.top;

			// Add one to the right and bottom sides, because the 
			// coordinates retrieved by GetClientRect do not 
			// include the far left and lowermost pixels. 

			ptClientLR.x = rcClient.right + 1;
			ptClientLR.y = rcClient.bottom + 1;
			ClientToScreen(hwnd, &ptClientUL);
			ClientToScreen(hwnd, &ptClientLR);

			// Copy the client coordinates of the client area 
			// to the rcClient structure. Confine the mouse cursor 
			// to the client area by passing the rcClient structure 
			// to the ClipCursor function. 

			SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
				ptClientLR.x, ptClientLR.y);
			ClipCursor(&rcClient);

			// Convert the cursor coordinates into a POINTS 
			// structure, which defines the beginning point of the 
			// line drawn during a WM_MOUSEMOVE message. 

			ptsBegin = MAKEPOINTS(lparam);
			return 0;
		}

		case WM_MOUSEMOVE:
		{

			// When moving the mouse, the user must hold down 
			// the left mouse button to draw lines. 

			if (wparam & MK_LBUTTON)
			{

				// Retrieve a device context (DC) for the client area. 

				hdc = GetDC(hwnd);

				// The following function ensures that pixels of 
				// the previously drawn line are set to white and 
				// those of the new line are set to black. 

				SetROP2(hdc, R2_NOTXORPEN);

				// If a line was drawn during an earlier WM_MOUSEMOVE 
				// message, draw over it. This erases the line by 
				// setting the color of its pixels to white. 

				if (fPrevLine)
				{
					MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
						(LPPOINT)NULL);
					LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
				}

				// Convert the current cursor coordinates to a 
				// POINTS structure, and then draw a new line. 

				ptsEnd = MAKEPOINTS(lparam);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
				LineTo(hdc, ptsEnd.x, ptsEnd.y);

				// Set the previous line flag, save the ending 
				// point of the new line, and then release the DC. 

				fPrevLine = TRUE;
				ptsPrevEnd = ptsEnd;
				ReleaseDC(hwnd, hdc);
			}
			break;

		}

		case WM_LBUTTONUP:
		{
			// The user has finished drawing the line. Reset the 
			// previous line flag, release the mouse cursor, and 
			// release the mouse capture. 

			fPrevLine = FALSE;
			ClipCursor(NULL);
			ReleaseCapture();
			return 0;
		}
		case WM_DESTROY: 
		{
			PostQuitMessage(0);
			break;
		}
			
		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASS wc = { 0 };

	DEVMODE dmScreenSettings;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Project";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;

	// Register the window class.
	RegisterClass(&wc);

	screenWidth = 1600;
	screenHeight = 900;


	// Create the window with the screen settings and get the handle to it.

	m_hwnd = CreateWindow(m_applicationName, m_applicationName, WS_OVERLAPPEDWINDOW, NULL, NULL, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}