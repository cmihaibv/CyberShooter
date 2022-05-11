////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <windows.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "graphicsclass.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "gameobjectmanager.h"
#include "cameraclass.h"
#include "mouse.h"
#include "Timer.h"
#include "CollisionEngine.h"



////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
////////////////////////////////////////////////////////////////////////////////
struct Gamedata
{
	enum GameState { MAINMENU, PLAY, LOST, SCORES, WON };
};


class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void InitialiseObjects();

	void Shutdown();
	void Run();

	bool UpdateDrawGamePlay(float);


	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	MouseClass m_mouse;
	Timer timer;

	CameraClass* m_camera;
	TextureManager* m_texManager;
	ModelManager* m_modelManager;
	GameObjectManager* m_gameObjectManager;
	CollisionEngine* m_collisionEngine;

	Gamedata::GameState mode = Gamedata::GameState::MAINMENU;


	std::vector<string> bulletsArray;
	float shootTimer;
};



static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0;


#endif