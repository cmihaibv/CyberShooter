#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

//////////////
// INCLUDES //
//////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "GameObjectManager.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	ID3D11Device* GetDevice();

	void SetCamera(CameraClass* cam);
	void GetGameObjectManager(GameObjectManager*);

private:
	bool Render();

private:
	D3DClass* m_D3D; // pointer to d3d instance
	CameraClass* m_Camera; // pointer to camera instance
	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	GameObjectManager* m_gameObjectManager;
};

#endif