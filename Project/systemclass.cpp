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


	// Create the camera object.
	m_camera = new CameraClass;
	if (!m_camera)
	{
		return false;
	}

	m_camera->InitialiseProjection(screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	// Set the initial position of the camera.
	m_camera->SetPosition(0.0f, 0.0f, -3.0f);

	// Send camera in Graphics
	m_Graphics->SetCamera(m_camera);


	//m_modelMGR = new ModelManager;
	//if (!m_modelMGR)
	//{
	//	return false;
	//}

	//m_modelMGR->SetDevice(m_Graphics->GetDevice());

	//m_modelMGR->GetHandle(m_hwnd);
	//m_modelMGR->SetTexture(L"../Project/data/guntex.dds");
	//m_modelMGR->SetMesh("../Project/data/mp5k.obj");
	//m_modelMGR->Set("gun");

	//m_modelMGR->GetModel
	
	return true;
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
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	//if (m_modelMGR)
	//{
	//	m_modelMGR->Shutdown();
	//	delete m_modelMGR;
	//	m_modelMGR = 0;
	//}

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


bool SystemClass::Frame()
{
	float dt = timer.GetMilisecondsElapsed();
	timer.Restart();

	bool result;


	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	float cameraVel = 0.1f;

	if (m_Input->IsKeyDown(0x28)) // move back
	{
		XMVECTOR moveBack = m_camera->GetBackwardVector() * cameraVel;

		m_camera->UpdatePosition(moveBack);
	}
	
	if (m_Input->IsKeyDown(0x26)) // move forward
	{
		XMVECTOR moveForward = m_camera->GetForwardVector() * cameraVel;

		m_camera->UpdatePosition(moveForward);
	}
	if (m_Input->IsKeyDown(0x25)) // move left
	{
		m_camera->UpdateRotation(0, -cameraVel, 0); // Yaw
	}
	if (m_Input->IsKeyDown(0x27)) // move right
	{
		m_camera->UpdateRotation(0, +cameraVel, 0); //Yaw
	}

	//MouseEvent ev = m_mouse.ReadEvent();
	//if (m_mouse.IsRightDown())
	//{
	//	this->m_camera->SetRotation(m_camera->GetRotation() + 20.05f, (float)ev.GetPosX() * 0.01f, 0);
	//	if (ev.GetType() == MouseEvent::EventType::RAW_MOVE)
	//	{
	//		
	//	}
	//}


	while (!m_mouse.EventBufferIsEmpty())
	{
		MouseEvent ev = m_mouse.ReadEvent();
		if (m_mouse.IsRightDown())
		{
			if (ev.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->m_camera->SetRotation((float)ev.GetPosY() + 0.05f, (float)ev.GetPosX() * 0.01f, 0);
			}
		}
	}


	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if(!result)
	{
		return false;
	}

	return true;
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