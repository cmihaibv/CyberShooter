#include "systemclass.h"
#include "Bullet.h"
#include "Enemy.h"

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

	m_texManager = new TextureManager;
	if (!m_texManager)
	{
		return false;
	}
	m_texManager->SetD3DDevice(m_Graphics->GetDevice());

	m_modelManager = new ModelManager;
	m_modelManager->SetD3DDevice(m_Graphics->GetDevice());

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
	m_camera->SetPosition(-30.0f, 0.0f, -30.0f);

	// Send camera in Graphics
	m_Graphics->SetCamera(m_camera);

	InitialiseObjects();



	
	return true;
}


void SystemClass::InitialiseObjects()
{
	//Initialise Textures
	m_texManager->InitialiseTexture("maptex", L"data/maptex.dds");
	m_texManager->InitialiseTexture("weapontex", L"data/UMP_lambert1_BaseColor.dds");
	m_texManager->InitialiseTexture("enemytex", L"data/Cyborg-Enemy_DIF.dds");
	m_texManager->InitialiseTexture("bullettex", L"data/Metal038_1K_Color.dds");
	m_texManager->InitialiseTexture("turrettex", L"data/Turret_lambert1_BaseColor.dds");
	m_texManager->InitialiseTexture("cctvtex", L"data/CCTV_lambert2SG_BaseColor.dds");

	// Load models
	m_modelManager->InitialiseModel("mapmodel", "data/map.obj");
	m_modelManager->InitialiseModel("umpmodel", "data/UMP.obj");
	m_modelManager->InitialiseModel("enemymodel", "data/enemymodel.obj");
	m_modelManager->InitialiseModel("bulletmodel", "data/bulletmats.obj");
	m_modelManager->InitialiseModel("turretmodel", "data/Turret.obj");
	m_modelManager->InitialiseModel("cctvmodel", "data/CCTV.obj");

	// Create gameobjects
	GameObject* map = new GameObject;
	map->SetName("map");
	map->SetD3DDevice(m_Graphics->GetDevice());
	map->SetTexture(m_texManager->GetTexture("maptex"));
	map->SetModel(m_modelManager->GetModel("mapmodel"));
	map->SetPosition(0, -2.0f, 0.f);
	map->SetRotation(0, 0, 0);
	m_gameObjectManager->AddGameObject(map, map->GetName());

	
	GameObject* gun = new GameObject;
	gun->SetName("gun");
	gun->SetTag("player");
	gun->SetD3DDevice(m_Graphics->GetDevice());
	gun->SetTexture(m_texManager->GetTexture("weapontex"));
	gun->SetModel(m_modelManager->GetModel("umpmodel"));
	gun->SetPosition(XMVectorGetX(m_camera->GetPosition()), -1.0, XMVectorGetZ(m_camera->GetPosition()));
	gun->SetRotation(XMVectorGetX(m_camera->GetRotation()), XMVectorGetY(m_camera->GetRotation()), XMVectorGetZ(m_camera->GetRotation()));
	gun->SetScale(0.1f, 0.1f, 0.1f);
	m_gameObjectManager->AddGameObject(gun, gun->GetName());

	//Enemy objects
	GameObject* testobj = new GameObject;
	testobj->SetName("testobj");
	testobj->SetTag("enemy");
	testobj->SetD3DDevice(m_Graphics->GetDevice());
	testobj->SetTexture(m_texManager->GetTexture("enemytex"));
	testobj->SetModel(m_modelManager->GetModel("enemymodel"));
	testobj->SetPosition(3,-3.5, 5);
	testobj->SetRotation(0, 0, 0);
	testobj->SetScale(5.0f, 5.0f, 5.0f);
	
	CollisionSphere* colsp = new CollisionSphere;
	colsp->UpdatePosition(testobj->GetPositionVec());
	colsp->SetRadius(3.0f);
	testobj->SetCollisionSphere(colsp);
	m_gameObjectManager->AddGameObject(testobj, testobj->GetName());


	//Enemy objects
	Enemy* enemyai = new Enemy;
	enemyai->SetName("enemyAI");
	enemyai->SetTag("enemy");
	enemyai->SetD3DDevice(m_Graphics->GetDevice());
	enemyai->SetTexture(m_texManager->GetTexture("enemytex"));
	enemyai->SetModel(m_modelManager->GetModel("enemymodel"));
	enemyai->SetPosition(7, -3.5, 5);
	enemyai->SetRotation(0, 0.5, 0);
	enemyai->SetScale(5.0f, 5.0f, 5.0f);

	CollisionSphere* enemysp = new CollisionSphere;
	enemysp->UpdatePosition(enemyai->GetPositionVec());
	enemysp->SetRadius(3.0f);
	enemyai->SetCollisionSphere(enemysp);
	m_gameObjectManager->AddGameObject(enemyai, enemyai->GetName());



	//Turret
	GameObject* turret = new GameObject;
	turret->SetName("turret");
	turret->SetD3DDevice(m_Graphics->GetDevice());
	turret->SetTexture(m_texManager->GetTexture("turrettex"));
	turret->SetModel(m_modelManager->GetModel("turretmodel"));
	turret->SetPosition(-27.06, 1, 0.28);
	turret->SetRotation(0, -4.46, 0);
	turret->SetScale(0.1f, 0.1f, 0.1f);

	CollisionSphere* turretsp = new CollisionSphere;
	turretsp->UpdatePosition(turret->GetPositionVec());
	turretsp->SetRadius(1.0f);
	turret->SetCollisionSphere(turretsp);
	m_gameObjectManager->AddGameObject(turret, turret->GetName());


	//CCTV
	GameObject* cctv = new GameObject;
	cctv->SetName("cctv");
	cctv->SetD3DDevice(m_Graphics->GetDevice());
	cctv->SetTexture(m_texManager->GetTexture("cctvtex"));
	cctv->SetModel(m_modelManager->GetModel("cctvmodel"));
	cctv->SetPosition(-18, 1, -22.63);
	cctv->SetRotation(0, -5.58, 0);
	cctv->SetScale(0.1f, 0.1f, 0.1f);

	m_gameObjectManager->AddGameObject(cctv, cctv->GetName());

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

	// Release the graphics object.
	if (m_texManager)
	{
		m_texManager->ReleaseTextures();
		delete m_texManager;
		m_texManager = 0;
	}
	// Release the graphics object.
	if (m_modelManager)
	{
		m_modelManager->ReleaseModels();
		delete m_modelManager;
		m_texManager = 0;
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
bool CheckNewPos(XMFLOAT3& move)
{
	int xMin = -18;
	int xMax = 13;

	int zMin = -23;
	int zMax = 15;

	vector<vector<int>> walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};

	vector<vector<vector<int>>> walkareas;
	walkareas.push_back(walkArea);

	xMin = -27;
	xMax = -18;

	zMin = -8;
	zMax = 0;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = -47;
	xMax = -27;

	zMin = -23;
	zMax = 15;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};

	walkareas.push_back(walkArea);

	xMin = -47;
	xMax = -40;

	zMin = -47;
	zMax = -23;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = -36;
	xMax = -23;

	zMin = -47;
	zMax = -27;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = -23;
	xMax = -11;

	zMin = -33;
	zMax = -27;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = -20;
	xMax = -12;

	zMin = -47;
	zMax = -27;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = -11;
	xMax = 16;

	zMin = -30;
	zMax = -27;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 5;
	xMax = 16;

	zMin = -46;
	zMax = -27;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = -20;
	xMax = 5;

	zMin = -47;
	zMax = -44;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 16;
	xMax = 19;

	zMin = -40;
	zMax = -38.5;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 19;
	xMax = 22;

	zMin = -47;
	zMax = -35;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 19;
	xMax = 32;

	zMin = -41;
	zMax = -39;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 29;
	xMax = 32;

	zMin = -47.6;
	zMax = -39;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 29;
	xMax = 47;

	zMin = -47.6;
	zMax = -46.95;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 31;
	xMax = 35;

	zMin = -44;
	zMax = -43;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 35;
	xMax = 47;

	zMin = -44;
	zMax = -42;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 19;
	xMax = 44;

	zMin = -32;
	zMax = -31;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 35;
	xMax = 36;

	zMin = -44;
	zMax = -31;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 40;
	xMax = 47;

	zMin = -44;
	zMax = -36;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 40;
	xMax = 43;

	zMin = -36;
	zMax = -31;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 35;
	xMax = 40;

	zMin = -37.5;
	zMax = -36;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 28;
	xMax = 31;

	zMin = -32;
	zMax = -27;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 19;
	xMax = 26;

	zMin = -32;
	zMax = -16;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 26;
	xMax = 32;

	zMin = -20.5;
	zMax = -16;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 31.5;
	xMax = 36;

	zMin = -16.8;
	zMax = -15.5;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);
	xMin = 35;
	xMax = 36;

	zMin = -16.8;
	zMax = -11.7;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 36;
	xMax = 45;

	zMin = -12.8;
	zMax = -11.7;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 40;
	xMax = 43;

	zMin = -17;
	zMax = -12.8;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 43;
	xMax = 44;

	zMin = -11.7;
	zMax = -8;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 40;
	xMax = 43;

	zMin = -9.5;
	zMax = 8;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 30;
	xMax = 43;

	zMin = 7;
	zMax = 8;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 19;
	xMax = 31;

	zMin = -8;
	zMax = 6;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 28;
	xMax = 32;

	zMin = 6;
	zMax = 16;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 19;
	xMax = 21;

	zMin = 6;
	zMax = 16;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 21;
	xMax = 32;

	zMin = 13;
	zMax = 16;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 31;
	xMax = 47;

	zMin = 15;
	zMax = 31;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	xMin = 44;
	xMax = 47;

	zMin = 31;
	zMax = 47;

	walkArea = {
		{ xMin, xMax},
		{ zMin, zMax}
	};
	walkareas.push_back(walkArea);

	for (int i = 0; i < walkareas.size();i++)
	{
		int a = walkareas.at(i)[0][1];
		if (move.x > walkareas.at(i)[0][0] && move.x < walkareas.at(i)[0][1])
		{
			if (move.z > walkareas.at(i)[1][0] && move.z < walkareas.at(i)[1][1])
			{
				return true;
			}
		}
	}

	return false;
}

void MoveCharacter(CameraClass* camera, GameObjectManager* gamemgr,InputClass* input,float dt)
{
	float cameraVel = 0.03f;

	//Store pointer of the gameobject into a variable
	GameObject* gameobj = gamemgr->GetGameObject("gun");

	//Save Actual position
	XMFLOAT3 actualCamPos;
	XMStoreFloat3(&actualCamPos, camera->GetPosition());
	XMFLOAT3 actualGunPos = gameobj->GetPosition();

	if (input->IsKeyDown(0x28) || input->IsKeyDown(0x53)) // Move camera and weapon back
	{
		// New position
		XMVECTOR moveBack = camera->GetBackwardVector() * cameraVel * dt;

		camera->UpdatePosition(moveBack);
		moveBack = gameobj->GetBackwardVector() * cameraVel * dt;
		
		gameobj->UpdatePosition(moveBack);


	}
	if (input->IsKeyDown(0x26) || input->IsKeyDown(0x57)) // Move camera and weapon forward
	{
		XMVECTOR moveForward = camera->GetForwardVector() * cameraVel * dt;
		camera->UpdatePosition(moveForward);

		moveForward = gameobj->GetForwardVector() * cameraVel * dt;
		gameobj->UpdatePosition(moveForward);
	}


	if (input->IsKeyDown(0x41)) // Move camera and weapon left
	{
		// New position
		XMVECTOR moveLeft = camera->GetLeftVector() * cameraVel * dt;

		camera->UpdatePosition(moveLeft);
		moveLeft = gameobj->GetLeftVector() * cameraVel * dt;
		
		gameobj->UpdatePosition(moveLeft);


	}
	if (input->IsKeyDown(0x44)) // Move camera and weapon forward
	{
		XMVECTOR moveRight = camera->GetRightVector() * cameraVel * dt;
		camera->UpdatePosition(moveRight);

		moveRight = gameobj->GetRightVector() * cameraVel * dt;
		gameobj->UpdatePosition(moveRight);
	}
	// Store new gun position
	XMFLOAT3 newGunPos = gameobj->GetPosition();

	//Check new position
	if (CheckNewPos(newGunPos) == false && input->IsKeyDown(0x10)==false)
	{
		camera->SetPosition(actualCamPos.x, actualCamPos.y, actualCamPos.z);
		gameobj->SetPosition(actualGunPos.x, actualGunPos.y, actualGunPos.z);
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
void TestCollision(CollisionEngine* collEngptr,GameObjectManager* gObjMgr)
{
	std::vector<string> collObjNames = collEngptr->TestCollision();

	if (collObjNames.size() != 0)
	{
		for (int i = 0;i < collObjNames.size();i++)
		{
			std::string name = collObjNames[i];
			if (collObjNames.size() > 0)
			{
				gObjMgr->RemoveGameObject(name);
			}
		}
	}
}

void Shoot(GameObject* obj,GameObjectManager* gObjMgr,ModelManager* mMgr,TextureManager* texMgr,GraphicsClass* graphics,vector<string>& bulletsArray)
{
	Bullet* bullet = new Bullet;
	
	string name = "bull" + std::to_string(gObjMgr->GetGameObjects().size()) + std::to_string(std::rand() % 100 + 1);		//random name
	bulletsArray.push_back(name);
	bullet->SetName(name);
	bullet->SetTag("bullet");
	bullet->AddCollidable("bullet");
	//bullet->AddCollidable("enemy");
	//bullet->AddCollidable("player");
	bullet->SetD3DDevice(graphics->GetDevice());
	bullet->SetTexture(texMgr->GetTexture("bullettex"));
	bullet->SetModel(mMgr->GetModel("bulletmodel"));
	bullet->SetPosition(obj->GetPosition().x, -1.0, obj->GetPosition().z);// under work
	bullet->SetRotation(XMVectorGetX(obj->GetRotation()), XMVectorGetY(obj->GetRotation()), XMVectorGetZ(obj->GetRotation()));
	bullet->SetScale(0.1f, 0.1f, 0.1f);
	

	CollisionSphere* bullsp = new CollisionSphere;
	bullsp->UpdatePosition(bullet->GetPositionVec());
	bullsp->SetRadius(1.0f);
	bullet->SetCollisionSphere(bullsp);
	gObjMgr->AddGameObject(bullet, bullet->GetName());
}
void CheckBulletsAlive(GameObjectManager* gObjMgr, vector<string>& bulletsArray)
{
	std::vector<string> updatedlist;
	for (int i=0; i<bulletsArray.size();i++)
	{
		if (gObjMgr->GetGameObject(bulletsArray.at(i)) != nullptr)
		{
			if (gObjMgr->GetGameObject(bulletsArray.at(i))->Alive() == true)
			{
				updatedlist.push_back(bulletsArray.at(i));		
			}
			else
			{
				gObjMgr->RemoveGameObject(bulletsArray.at(i));	// remove if the bullet dead
			}		
		}	
	}
	bulletsArray = updatedlist;
}
void UpdateBulletsPosition(GameObjectManager* gObjMgr, vector<string>& bulletsArray)
{
	for (int i = 0; i < bulletsArray.size();i++)
	{

		if (gObjMgr->GetGameObject(bulletsArray.at(i)) != nullptr)
		{
			gObjMgr->GetGameObject(bulletsArray.at(i))->Action();
		}

	}
}

bool SystemClass::UpdateDrawGamePlay(float dt)
{
	bool result;

	//move character each frame
	MoveCharacter(m_camera,m_gameObjectManager,m_Input,dt);


	//Shoot 

	//Check what bullets are allive if any

	// Timer for shooting
		shootTimer += dt;
	if (m_Input->IsKeyDown(0x20) && shootTimer>100.f)
	{
		GameObject* obj = m_gameObjectManager->GetGameObject("gun");
		Shoot(obj,m_gameObjectManager, m_modelManager, m_texManager, m_Graphics,bulletsArray);
		shootTimer = 0;
	}
	if (bulletsArray.size() != 0)
	{
		CheckBulletsAlive(m_gameObjectManager, bulletsArray);
		UpdateBulletsPosition(m_gameObjectManager, bulletsArray);
	}
	
	//Chase player
	chaseTimer += dt;
	if (chaseTimer > 20.0)
	{
		m_gameObjectManager->GetGameObject("enemyAI")->Action(m_gameObjectManager->GetGameObject("gun"));
		if (State::SHOOT == m_gameObjectManager->GetGameObject("enemyAI")->GetState())
		{
			GameObject* obj = m_gameObjectManager->GetGameObject("enemyAI");
			Shoot(obj,m_gameObjectManager, m_modelManager, m_texManager, m_Graphics, bulletsArray);
		}
		chaseTimer = 0;
	}
	

	//Test collision between objects
	TestCollision(m_collisionEngine, m_gameObjectManager);


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
		result = UpdateDrawGamePlay(dt);	
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
	m_applicationName = L"Shooter Game - The New Noir";

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